fp = fopen('SHUJU5.txt');
data=fgetl(fp);
fclose(fp);
str_posi=strfind(data,'0D 0A');
data_num=zeros(length(str_posi),1);
for i=1:length(str_posi)
    data_num(i)=hex2dec(data(str_posi(i)-9:str_posi(i)-8))*256*256+hex2dec(data(str_posi(i)-6:str_posi(i)-5))*256+hex2dec(data(str_posi(i)-3:str_posi(i)-2));
end
plot(data_num(1000:1500))

%% filtering
Ts=0.004444;
fs=1/Ts;
NLen=length(data_num);
n=0:NLen-1;
f0=50;
apha=-2*cos(2*pi*f0*Ts);
beta=0.96;
b=[1 apha 1];
a=[1 apha*beta beta^2];
figure(1);
freqz(b,a,NLen,fs);
y=filter(b,a,data_num);
%plot(data_num(1:5000))
%%
xfft=fft(data_num,NLen);
xfft=xfft.*conj(xfft)/NLen;
y1=fft(y,NLen);
y2=y1.*conj(y1)/NLen;
figure(2);%comparsion
subplot(2,2,1);plot(n,data_num);grid;
xlabel('Time (s)');ylabel('Amplitude');title('Input signal');
subplot(2,2,3);plot(n,y);grid;
xlabel('Time (s)');ylabel('Amplitude');title('Filter output');
subplot(2,2,2);plot(n*fs/NLen,xfft);xlim([10 150]) ;
xlabel('Frequency (Hz)');ylabel('Magnitude (dB)');title('Input signal');
subplot(2,2,4);plot(n*fs/NLen,y2);xlim([10 150]) ;
xlabel('Frequency (Hz)');ylabel('Magnitude (dB)');title('Filter output');