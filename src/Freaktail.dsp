

UserFeBa = (hslider("Decay", 0.81, 0.1, 1, 0.01):max(0):min(1));//Amount of feedback for the delaylines
UserTime= (hslider("Roomsize", 0.8, 0.01, 5, 0.01):max(0.1):min(5):_<:_@1+_);
Drive=hslider("Drive",1, 1, 49, 0.5):max(1):min(49):_-50:_*-1;	
Distort = _/Drive:((_*0.996:_@1:_)-_~_);
Gain = (hslider("Gain", 0.81, 0.1, 1, 0.01):max(0):min(1));

delline1(i) = (_+_)~(_@(i*UserTime:int):_*UserFeBa);							//Building block for the longer delaylines
DC = _<:((_+_:_@1:_)-_~_*0.9996);

Febaroute2 = 	_,_<:
				delline1(301),delline1(461),delline1(1025),delline1(1317),
				delline1(1723),delline1(2317),delline1(2913),delline1(506),
				delline1(2600),delline1(3137),delline1(3581),delline1(3583),
				delline1(3659),delline1(3727)
 :>_,_;


																
process =_*Gain,_*Gain:Febaroute2:DC,DC:((_<:(_,Distort):_+_):max(-1):min(1)),((_<:(_,Distort):_+_):max(-1):min(1));
//filtered=0.996 × (last_filtered_value + sample - last_sample)
