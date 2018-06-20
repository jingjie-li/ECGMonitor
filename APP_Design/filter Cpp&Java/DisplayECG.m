figure
x = load('ecgdata_raw.txt');
y = load('out.txt');
NLen = length(y);

subplot(2,2,1)
plot((x-5900000)/80);
xfft=fft(x,NLen);
xfft=xfft.*conj(xfft)/NLen;
subplot(2,2,2);
plot((0:NLen-1)*225/NLen,xfft);xlim([10 200]) ;
xlabel('Frequency (Hz)');ylabel('Magnitude (dB)');title('Input signal');

subplot(2,2,3)
plot(y,'r');
yfft=fft(y,NLen);
yfft=yfft.*conj(yfft)/NLen;
subplot(2,2,4);
plot((0:NLen-1)*225/NLen,yfft);xlim([10 200]) ;
xlabel('Frequency (Hz)');ylabel('Magnitude (dB)');title('Input signal');
%%
x = load('ecgdata_raw.txt');
y = load('out_1.txt');
subplot(2,1,1)
plot(x(51:1000)-5900000);

subplot(2,1,2)
plot(y(51:1000),'r');

