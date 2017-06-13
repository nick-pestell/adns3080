clear all
clc
dbstop if error

arduino = serial('COM3','BaudRate',115200);

fopen(arduino);

figure
h = animatedline;


%% dX
% ylabel('dX');
% for i=1:2000
%    axis([i-200,i,-128,127])
%    y(i) = fscanf(arduino,'%d');
%    addpoints(h,i,y(i))
%    drawnow update
% end

%% dy
% ylabel('dY');
% for i=1:2000
%    axis([i-200,i,-128,127])
%    y(i) = fscanf(arduino,'%d');
%    addpoints(h,i,y(i))
%    drawnow update
% end

%% Image Quality
ylabel('Image Quality');
time = [1:2000];
for i=1:2000
   axis([i-200,i,0,169])
   y(i) = fscanf(arduino,'%d');
   addpoints(h,i,y(i))
   drawnow update
end

%% Shutter Spead
% ylabel('Shutter Spead');
% for i=1:2000
%    axis([i-200,i,0,255])
%    y(i) = fscanf(arduino,'%d');
%    addpoints(h,i,y(i))
%    drawnow update
% end

%% Max Pixel
% ylabel('Maximum Pixel Value');
% for i=1:2000
%     axis([i-200,i,0,65])
%     y(i) = fscanf(arduino,'%d');
%     addpoints(h,i,y(i))
%     drawnow update
% end

fclose(arduino);