import("music.lib");
import("filter.lib");


A=0;
IL = _;
IR = _;
maximum=15;

//1 Early reflection (building block)
Del(i) = ((IL,IR<:((_-_:delay(65536,(((DelTime)*i):int:max(1)))),(_+_))))
with
{
//UserInput to change the basic pre-delays
DelTime = (hslider("Blur", 0.6, 0, maximum, 0.1):max(0):min(30)):smooth(0.999);
};


Early = (_,_:Del(0):Del(1):Del(2):Del(5):Del(7):Del(23):Del(54):Del(79):
        Del(220):Del(340):Del(454):Del(623):Del(845):Del(1304):Del(1532):
        Del(2204):Del(3137):Del(3567):Del(4218));


Gain = _*(hslider("Level", 0.2, 0.0, 1.5,0.001):max(0.0):min(1.5)):smooth(0.999);


process=Early:(Gain:max(-1):min(1)),(Gain:max(-1):min(1)):dcblocker,dcblocker;
