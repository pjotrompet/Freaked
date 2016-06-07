import("music.lib");
import("effect.lib");
import("filter.lib");
import("math.lib");
import("oscillator.lib");




MIDIN=(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
31,32,33,34,35,36,37,38,39,40,41,42,42,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,
59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,
93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,
115,116,117,118,119,120,121,122,123,124,125,126,127);

scale(N)=
take(1,MIDIN),
take(3,MIDIN),
take(5,MIDIN),
take(6,MIDIN),
take(8,MIDIN),
take(10,MIDIN),
take(12,MIDIN):
par(i,7,_+N);

ftom(f)=69+12*log1p(f/440);
mtof(nn)=2^((nn-69)/12)*440;



Mfilter(freq)=_:moog_vcf(hslider("re[style:knob]", 0.2, 0, 0.9, 0.1), freq):_;

selectN(N,i) = S(N,0)
    with {
       S(1,offset) = _;
       S(n,offset) = S(left, offset), S(right, offset+left) : select2(i >= offset+left)
            with {
                right = int(n/2);
                left  = n-right;
            };
    };


mod(sc,r)=((scale(sc):selectN(7,(lfnoise(10):latch(lf_pulsetrainpos(r,0.9)))*7)));

freakfilter=_<:
(Mfilter(mod(sc:_+12+12*octv,r):mtof)<:_,_),
_*dry,_*dry,
(Mfilter(mod(sc:_+0+12*octv,r):mtof)<:_,_),
(Mfilter(mod(sc:_+24+12*octv,r):mtof)<:_,_)
:>echo2s,echo2s
with
{
sc=hslider("scale[style:knob]", 7, 0, 12, 1);
r=hslider("rate[style:knob]", 0.2, 0, 10, 0.1);
dry=hslider("dry[style:knob]", 0.2, 0, 0.9, 0.1);
octv=hslider("octv[style:knob]", 1, 1, 5, 1):smooth(0.99);
};


process = freakfilter;
