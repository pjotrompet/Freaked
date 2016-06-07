declare name "Granulator";
declare author "Mayank Sanganeria";
declare version "1.2";
declare maintainer "Pjotr Lasschuit";

//Pjotr did some minor changes, and added a mix knob. Also he is porting it to the MOD repo (http://moddevices.com)


import ("filter.lib") ;
import ("math.lib") ;


// Globals
samplera = SR:int;
counter = _+(1)%delayLength~_; // to iterate through the delay line
delayBufferSize = 480000;
maxN = 16;


// Controls
N = hslider("grain density", 2, 2, maxN, 1);
gLength = hslider("grain length", 0.1, 0.01, 0.5, 0.01):smooth(0.999);
dLength = hslider("delay length", 10, 0.5, 10, 0.1):smooth(0.999);
mix=hslider("mix", 0.5, 0, 1, 0.01):smooth(0.999);

//Granular synth variables
grainLength = int(samplera*gLength);
delayLength = int(samplera*dLength);



//noisey Generator

S(1,F) = F;
S(i,F) = F <: S(i-1,F),_ ;
Divide(n,k) = par(i, n, /(k)) ;
random2 = +(12345) : *(1103515245) ;
random2aximum = 2^32 - 1 ;
chain(n) = S(n,random2) ~ _;
noiseyN(n) = chain(n) : Divide(n,random2aximum);

noiseyr = noiseyN(maxN+1);                          //multi channel noiseyr

noiseyChan(n,0) = noiseyr:>_,par( j, n-1 , !);
noiseyChan(n,i) = noiseyr:>par( j, i , !) , _, par( j, n-i-1,!);

noisey(i) = (noiseyChan(maxN+1,i) + 1) / 2; //get nth channel of multi-channel noiseyr
//-------------noisey Generator End

//Sample & Hold
SH(trig,x) = (*(1 - trig) + x * trig) ~ _;


//Grain Positions
grainOffset(i) = int(SH(1-1',int(delayLength*noisey(i)))) ;
grainCounterMaster = +(1)%grainLength~_;      // universal counter for all grains
grainCounter(i) = (grainCounterMaster + grainOffset(i) ) % grainLength;
grainrandom2StartPos(i) = int(SH(int(grainCounter(i)/(grainLength-1)),int(delayLength*noisey(i))));
grainPosition(i) = grainCounter(i) + grainrandom2StartPos(i);

//Delay Line
buffer(write,read,x) = rwtable(delayBufferSize, 0.0, write%delayLength, x, read%delayLength);

//sin wave for windowing
window(i) = sin(2*3.14159*grainCounter(i)/(grainLength-1));

process = _,_<:_*(mix*-1+1),_*(mix*-1+1),par(i,maxN,buffer(counter, grainPosition(i))*window(i)*(i<N)*mix*2):> _,_;
