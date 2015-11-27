Delay=hslider("Delay",0.996, 0, 1, 0.01); 
Drive=hslider("Drive",1, 1, 9.9, 0.1):max(1):min(9.9):_-10:_*-1;	
Distort = _/Drive:((_*Delay:_@1:_)-_~_);

process = (_<:(_,Distort):_+_);