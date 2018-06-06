classdef plotDat < handle
    properties
        arduino
    end
    
    methods
        function self = plotDat()
            self.arduino = serial('COM8');
            self.arduino.InputBufferSize = 1;
            self.arduino.Baudrate = 9600;
            try 
                fopen(self.arduino);
            catch err
                fclose(instrfind);
                error('incorect com port');
            end
        end
        
        function data = readDat(self)
            data = fread(self.arduino);
        end
        
        function close(self)
            fclose(self.arduino);
        end
        
        function delete(self)
            fclose(self.arduino);
        end
    end
end

