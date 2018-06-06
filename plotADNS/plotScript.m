dbstop if error
clear all

sensor = plotDat()

Tmax = 50;
figure
grid on;
xlabel('Time(s)');
Ts = 0.001; i = 0; data = 0; t = 0;

pause(5);
tic;

%% image quality
ylabel('Image Quality');
while toc <= Tmax
    i = i +1;
    data(i) = sensor.readDat();
    timeS(i) = toc;
    t(i) = toc;
    if i > 1
        T = toc - t(i-1);
        while T <Ts
            T = toc - t(i-1);
        end
    end
    t(i) = toc;
    if i > 1
        axis([toc-5 toc+5 40 90]);
        line([t(i-1) t(i)],[data(i-1) data(i)],'color','g','linewidth',2)
        %plot(t(i),data(i));
        set(gca, 'color', 'black')
        set(gca, 'GridColor', 'white')
        drawnow
    end
    cla

end

sensor.close();
