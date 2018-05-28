%% Import data table
datatable = importdata('serial_data.txt', '\n');
%% Getout the datestr, count, temp, humd
data = cell(length(datatable)-5,3);
for i=1:length(datatable)
    Istart = strfind(datatable{i},'ECG Channel I Data: ')+20;
    Iend = strfind(datatable{i},'ECG Channel II')-1;
    IIstart = strfind(datatable{i},'ECG Channel II Data: ')+21;
    IIend = strfind(datatable{i},'ECG Channel III')-1;
    IIIstart = strfind(datatable{i},'ECG Channel III Data: ')+22;
    IIIend = length(datatable{i})-1;
    I = str2double(datatable{i}(Istart:Iend)); % counts
    II = str2double(datatable{i}(IIstart:IIend)); % temp
    III = str2double(datatable{i}(IIIstart:IIIend)); % humd
    data{i,1} = I;
    data{i,2} = II;
    data{i,3} = III;
end
%%
namestr = {'EcgCh1','EcgCh2','EcgCh3'};
data = cell2table(data,'VariableNames',namestr);
writetable(data,'ecgdata.csv')
%% example
plot(data.EcgCh1)