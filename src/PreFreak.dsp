A=0;
IL = _; 															
IR = _;
Gain = _/((hslider("PreGain", 1,1,999,0.5):max(0):min(999)):_-1000:_*-1);		
Drive=hslider("Drive",1, 1, 999, 0.5):max(1):min(999):_-1000:_*-1;									
DelTime = (hslider("Pre-DelTime's", 0.6, 0, 15, 0.1):max(0):min(30)):seq(i, 2, (_<:_@1+_));			//UserInput to change the basic pre-delays (same
Del(i) = ((IL,IR<:((_-_:_@(((DelTime)*i):int:max(1))),(_+_))));		//1Early reflection (building block)
Distort = _/Drive:((_*0.996:_@1:_)-_~_);
DC = _<:((_+_:_@1:_)-_~_*0.996);

Early = (_,_:Del(0):Del(1):Del(2):Del(5):Del(7):Del(23):Del(54):Del(79):	Del(220):Del(340):Del(454):Del(623):Del(845):Del(1304):Del(1532):Del(2204):Del(3137):Del(3567):Del(4218));

process=Early:(Gain:max(-1):min(1)),(Gain:max(-1):min(1));