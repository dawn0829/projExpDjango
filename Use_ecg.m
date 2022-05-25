clear ;
data = readcell('ECGdata3.csv');
ecg_i = str2double(data);
clear data;
ecg_i = ecg_i.'*0.0012;
t = 1:length(ecg_i);
plot(t,ecg_i(1,:));
