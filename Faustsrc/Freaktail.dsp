import("music.lib");
import("filter.lib");


Gain = (hslider("Tail level", 0.81, 0.1, 1, 0.01):max(0):min(1));


//Distortion Algorithm

Distort=(_<:(_,(_/Drive:((_*0.99:_@1:_)-_~_))):_+_):max(-1):min(1):dcblocker
with {
	Drive=hslider("Drive",1, 1, 9.9, 0.1):max(1):min(9.9):_-10:_*-1:smooth(0.999);
};






delline1(i) = (_+_)~(_@(i*UserTime:int):_*UserFeBa)
with
{
UserFeBa = (hslider("Decay", 0.81, 0.1, 1, 0.01):smooth(0.999):max(0):min(1));//Amount of feedback for the delaylines
UserTime= (hslider("Roomsize", 0.8, 0.01, 5, 0.01):smooth(0.999):max(0.1):min(5):_<:_@1+_);
};


Febaroute2 = 	_,_<:
				delline1(301),delline1(461),delline1(1025),delline1(1317),
				delline1(1723),delline1(2317),delline1(2913),delline1(506),
				delline1(2600),delline1(3137)

 :>_,_;



process =_*Gain,_*Gain:Febaroute2:dcblocker,dcblocker:(max(-1):min(1)),(max(-1):min(1));
//filtered=0.996 × (last_filtered_value + sample - last_sample)
//((_<:(_,Distort):_+_):max(-1):min(1)),((_<:(_,Distort):_+_):
