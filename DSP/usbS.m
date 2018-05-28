s=serial('/dev/tty.usbmodem1421');
set(s,'BaudRate',115200,'StopBits',1,'Parity','none','DataBits',8,'InputBufferSize',255);
fopen(s);
fwrite(s,'Z');a = fread(s);
fprintf('%s\n',char(a)')
fwrite(s,'Z');a=fread(s,10000,'uint8'); fprintf('%s\n',char(a)');

a=fread(s,10000,'uint8'); fprintf('%s\n',char(a)');

fwrite(s,hex2dec('11'));a = fread(s);fprintf('%s\n',char(a)')
%%
flushinput(s)
fid=fopen('serial_data.txt','w+');
starttime=now;
dur=100;
while (now-starttime)*24*60*60<dur
    out=fread(s,255,'uint8'); 
    fprintf(fid,'%s',char(out)'); 
    fprintf('%s',char(out)');
end
fclose(fid);  