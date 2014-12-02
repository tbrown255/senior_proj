s = serial('COM5');
set(s,'BaudRate',9600);
set(s,'DataBits',8);
set(s,'Terminator',73);
set(s,'StopBits',1);

go = 0;
fopen(s);
s.ReadAsyncMode = 'manual';
readasync(s);

    while go ~= 255
        go = fread(s,1);
    end
    data = fread(s, 16);
    


%data(1)= data(1)
%data(9)= data(9)+20;
%data(4)= data(4)+35;
%data(5)= data(5)+40;
%data(7)= data(7)+40;
%data(8)= data(8)+30;
%data(9)= data(9)+20;
%data(10)= data(10)+30;
%data(11)= data(11)+25;
%data(12)= data(12)+40;
%data(13)= data(13);
%data(14)= data(14)+25;
%data(16)= data(16)+20;

sensor(1,1) = data(16);
sensor(1,2) = data(8);
sensor(1,3) = data(7);
sensor(1,4) = data(11);
sensor(2,1) = data(4);
sensor(2,2) = data(12);
sensor(2,3) = data(15);
sensor(2,4) = data(3);
sensor(3,1) = data(10);
sensor(3,2) = data(6);
sensor(3,3) = data(5);
sensor(3,4) = data(13);
sensor(4,1) = data(2);
sensor(4,2) = data(14);
sensor(4,3) = data(9);
sensor(4,4) = data(1);
sensor()

%end
%data = fscanf(s,'%f');

flushinput(s);
fclose(s);
delete(s)
clear s