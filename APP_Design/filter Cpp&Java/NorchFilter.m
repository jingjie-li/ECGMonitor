clear all
Ts = 0.0046;
fs=1/Ts;           %数字滤波器的采样频率fs=1000hz
f=50;              %Phz的正弦信号
% t=0:Ts:4;      %时间间隔，ADC采样频率250hz
% s=sin(2*pi*f*t)+cos(2*pi*2*f*t);
s = load('ecgdata_raw.txt');
%%
IIR_B=[0.930936,-0.22854019,0.93093678];
IIR_A= [1,-0.22854019,0.86187357];

w01=0;
w02=0;
w03=0;

for i=1:length(s)-1
    w01=s(i)-IIR_A(2)*w02-IIR_A(3)*w03;
    y0(i)=IIR_B(1)*w01+IIR_B(2)*w02+IIR_B(3)*w03;

    w03=w02;
    w02=w01;
end


%%
figure
subplot(211)

plot(s(51:1000));
title('直接II型实现—原始信号时域');
subplot(212)
plot(y0(51:1000),'r');ylim([min(s(51:1000)) max(s(51:1000))])
title('直接II型实现—信号滤波之后');