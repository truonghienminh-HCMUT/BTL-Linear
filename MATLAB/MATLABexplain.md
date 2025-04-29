GIẢI THÍCH CODE MATLAB

# 1. Khai báo các nút, ô, đồ thị, khối,... trong app

'''
classdef Linear < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure                 matlab.ui.Figure
        thPanel                  matlab.ui.container.Panel
        ngingnnhtEditField       matlab.ui.control.EditField
        ngingnnhtEditFieldLabel  matlab.ui.control.Label
        WeightEditField          matlab.ui.control.NumericEditField
        ShngvctLabel_2           matlab.ui.control.Label
        UIAxes                   matlab.ui.control.UIAxes
        DliuPanel                matlab.ui.container.Panel
        MatrnOutputLabel         matlab.ui.control.Label
        MatrnInputLabel          matlab.ui.control.Label
        OutputTable              matlab.ui.control.Table
        InputTable               matlab.ui.control.Table
        Panel                    matlab.ui.container.Panel
        PlotGraphButton          matlab.ui.control.Button
        ConfirmButton            matlab.ui.control.Button
        Label_2                  matlab.ui.control.Label
        HeadDropDown             matlab.ui.control.DropDown
        TailDropDown             matlab.ui.control.DropDown
        uiDropDownLabel          matlab.ui.control.Label
        uDropDownLabel           matlab.ui.control.Label
        ngicntmLabel             matlab.ui.control.Label
        Label                    matlab.ui.control.Label
        NumofVerticesEditField   matlab.ui.control.NumericEditField
        SnhEditFieldLabel        matlab.ui.control.Label
        NumofEdgesEditField      matlab.ui.control.NumericEditField
        ShngvctLabel             matlab.ui.control.Label
        CalculateButton          matlab.ui.control.Button
        ResetButton              matlab.ui.control.Button
        CreateTableButton        matlab.ui.control.Button
        UndirectedButton         matlab.ui.control.Button
        DirectedButton           matlab.ui.control.Button
        Name                     matlab.ui.control.Label
        Group                    matlab.ui.control.Label
    end

'''

# 2. Các lệnh được sử dụng trong các thành phần của app

## 2.1. Nút Undirected:

'''
function UndirectedButtonPushed(app, event)
    app.DirectedButton.Enable="off";
    app.ResetButton.Enable="on";

    app.NumofEdgesEditField.Enable="on";
    app.NumofVerticesEditField.Enable="on";
    app.CreateTableButton.Enable="on";

    app.UndirectedButton.BackgroundColor=[0.07,0.62,1.00];
end
'''

Khi nhấn vào nút Undirected, nút Directed sẽ tắt thông qua lệnh "off", các nút Reset, CreateTableButton ô NumofEdgesEditField, NumofVerticesEditField sẽ bật thông qua lệnh "on", đồng thời thay màu của nút Undirected sang xanh.

## 2.2. Nút Directed

'''
function DirectedButtonPushed(app, event)
    app.UndirectedButton.Enable="off";
    app.ResetButton.Enable="on";

    app.NumofEdgesEditField.Enable="on";
    app.NumofVerticesEditField.Enable="on";
    app.CreateTableButton.Enable="on";

    app.DirectedButton.BackgroundColor=[0.07,0.62,1.00];
end
'''

Các lệnh trong nút Directed sẽ có chức năng tương tự như nút Undirected

## 2.3. Nút Reset

'''
function ResetButtonPushed(app, event)
    app.UndirectedButton.Enable="on";
    app.DirectedButton.Enable="on";
    app.CalculateButton.Enable="off";
    app.ResetButton.Enable="off";
    app.ConfirmButton.Enable="off";
    app.PlotGraphButton.Enable="off";

    app.NumofEdgesEditField.Enable="off";
    app.NumofVerticesEditField.Enable="off";
    app.CreateTableButton.Enable="off";

    app.DirectedButton.BackgroundColor=[0.96,0.96,0.96];
    app.UndirectedButton.BackgroundColor=[0.96,0.96,0.96];

    data = cell(0, 0);
    app.InputTable.Data = data;
    app.OutputTable.Data = data;

    app.NumofEdgesEditField.Value=0;
    app.NumofVerticesEditField.Value=0;
    app.WeightEditField.Value=0;
    app.ngingnnhtEditField.Value="0";

    app.HeadDropDown.Items = {};
    app.TailDropDown.Items = {};

    cla(app.UIAxes,'reset')
end
'''

Sau khi nhấn nút Reset, chương trình sẽ quay về trạng thái ban đầu

## 2.4. Nút CreateTable

'''
function CreateTableButtonPushed(app, event)
    fig=app.UIFigure;
    if app.DirectedButton.Enable=="on"
        if mod(app.NumofVerticesEditField.Value, 1) ~= 0 || app.NumofVerticesEditField.Value<=0
            message = "Số đỉnh phải là số nguyên dương.";
            uialert(fig,message,"Warning", "Icon","error");
            return

        elseif mod(app.NumofEdgesEditField.Value, 1) ~= 0 || app.NumofEdgesEditField.Value<0
            message = "Số cạnh phải là số nguyên không âm.";
            uialert(fig,message,"Warning", "Icon","error");
            return

        elseif app.NumofEdgesEditField.Value>app.NumofVerticesEditField.Value*app.NumofVerticesEditField.Value
            message = "Lỗi vượt quá giới hạn số cạnh.";
            uialert(fig,message,"Warning", "Icon","error");
            return
            
        end

    elseif app.UndirectedButton.Enable=="on"
        if mod(app.NumofVerticesEditField.Value, 1) ~= 0 || app.NumofVerticesEditField.Value<=0
            message = "Số đỉnh phải là số nguyên dương.";
            uialert(fig,message,"Warning", "Icon","error");
            return

        elseif mod(app.NumofEdgesEditField.Value, 1) ~= 0 || app.NumofEdgesEditField.Value<0
            message = "Số cạnh phải là số nguyên không âm.";
            uialert(fig,message,"Warning", "Icon","error");
            return

        elseif app.NumofEdgesEditField.Value>(app.NumofVerticesEditField.Value*(app.NumofVerticesEditField.Value+1))/2
            message = "Lỗi vượt quá giới hạn số cạnh.";
            uialert(fig,message,"Warning", "Icon","error");
            return

        end
    end
            
            
    app.PlotGraphButton.Enable="on";
    app.CreateTableButton.Enable = "off";
    app.NumofEdgesEditField.Enable="off";
    app.NumofVerticesEditField.Enable="off";
            
                      
    Num = round(app.NumofEdgesEditField.Value);                  
           
    datain = cell(Num, 3);
    dataout = cell(Num, Num);

    app.InputTable.Data = datain;
    app.OutputTable.Data = dataout;

    Names = arrayfun(@(x) sprintf('%d', x), 1:Num, 'UniformOutput', false);
    app.OutputTable.ColumnName = Names;
    app.OutputTable.RowName = Names;
    app.InputTable.RowName = Names;

    Names = arrayfun(@(x) sprintf('%d', x), 1:3, 'UniformOutput', false);
    app.InputTable.ColumnName = Names;

    app.OutputTable.Enable = "off";
    app.OutputTable.Enable="inactive";
end
'''

Sau khi nhấn nút CreateTable, chương trình sẽ dựa vào số đỉnh và số cạnh từ người dùng nhập để tạo ma trận nhập số liệu. Nếu dữ liệu nhập nằm trong các trường hợp lỗi, chương trình sẽ thông báo những lỗi như sau:
- Số đỉnh phải là số nguyên dương
- Số cạnh phải là số nguyên không âm
- Lỗi vượt quá giới hạn số cạnh

## 2.5. Nút Calculate

'''
function CalculateButtonPushed(app, event)
    app.CalculateButton.Enable="off";
    fig = app.UIFigure;          
        
    system('run.exe')
            
    M = str2double(app.HeadDropDown.Value);
    N = str2double(app.TailDropDown.Value);

    fileID = fopen('output.txt', 'r');
    if fileID == -1
    message = "Error opening file.";
    uialert(fig,message,"Warning", "Icon");
    return;
    end
    numVertices = app.NumofVerticesEditField.Value;
    n = numVertices;
    data = cell(n, n);           

    for i = 1:n
        line = fgetl(fileID);
        if ~ischar(line)
            message = 'Error reading file, or file does not match expected size.';
            uialert(fig,message,"Warning", "Icon","error");
            fclose(fileID);
            return;
        end
        values = strsplit(strtrim(line));
        for j = 1:n
            if strcmpi(values{j}, "INF")
                data{i, j} = Inf;
            elseif strcmpi(values{j}, "-INF")
                data{i, j} = -Inf;
            else
                data{i, j} = str2double(values{j});
            end
        end
    end
            

    numbersLine = ''; 
    while ~feof(fileID)
        lastLine = fgetl(fileID);
        if ischar(lastLine)
            numbersLine = strtrim(lastLine);
        end
    end
    fclose(fileID);

    app.ngingnnhtEditField.Value=numbersLine;
    app.OutputTable.Data = data;


    pathNodes = str2num(numbersLine);
        
    datainput = app.InputTable.Data;  
    x = str2double(datainput(:, 1));
    y = str2double(datainput(:, 2));
    z = str2double(datainput(:, 3));

    if app.DirectedButton.Enable == 1
        G = digraph(x, y, z, numVertices);
    elseif app.UndirectedButton.Enable == 1
        G = graph(x, y, z, numVertices);
    end   

    p = plot(app.UIAxes, G, 'EdgeLabel', G.Edges.Weight);

    if length(pathNodes) >= 2
        highlightEdges = [];
        for i = 1:length(pathNodes) - 1
            highlightEdges = [highlightEdges; pathNodes(i), pathNodes(i + 1)];
        end
    highlight(p, highlightEdges(:,1), highlightEdges(:,2), 'EdgeColor', 'red', 'LineWidth', 2);
    highlight(p, pathNodes, 'NodeColor', 'red', 'MarkerSize', 8);

    elseif isscalar(pathNodes)
        highlight(p, pathNodes, 'NodeColor', 'red', 'MarkerSize', 8);
    end
            
    app.WeightEditField.Value=data{M, N};
    data = data{1};
    numRows = length(data);
    if numRows == 0
        app.UITable.Data = [];
        return;
    end

end
'''

Chương trình sẽ chạy chương trình C++, lấy dữ liệu được xuất ra từ file output.txt và tiến hành vẽ đồ thị cũng như xuất kết quả vào ô kết quả

## 2.6. Nút Confirm

'''
function ConfirmButtonPushed(app, event)
    fig = app.UIFigure;
    data = app.InputTable.Data;
            
    firstColumn = data(:, 1);
    secondColumn = data(:, 2);

    combinedColumns = [firstColumn; secondColumn];
    uniqueValues = unique(combinedColumns);

    numUnique = length(uniqueValues);
            
            
    if numUnique>app.NumofVerticesEditField.Value
        message = ["Lỗi vượt quá số đỉnh trong ma trận Input.", "Hãy nhập lại ma trận."];
        uialert(fig,message,"Warning", "Icon","error");
        return
    end
            

    fileID = fopen('input.txt', 'w');

    fprintf(fileID, '%s ', string(app.NumofVerticesEditField.Value));
    fprintf(fileID, '%s ', string(app.NumofEdgesEditField.Value));
    if app.DirectedButton.Enable == 1
        fprintf(fileID, '%s ', string(1));
    elseif app.UndirectedButton.Enable == 1
        fprintf(fileID, '%s ', string(0));
    end
    fprintf(fileID, '\n');

    [rows, cols] = size(data);
    for i = 1:rows
        for j = 1:cols
            fprintf(fileID, '%s ', string(data{i, j}));
        end
        fprintf(fileID, '\n');
    end
                      
    fprintf(fileID, '%s ', string(1));
    fprintf(fileID, '\n');
    fprintf(fileID, '%s ', string(app.HeadDropDown.Value));
    fprintf(fileID, '%s ', string(app.TailDropDown.Value));
    fclose(fileID);

    app.HeadDropDown.Enable="off";
    app.TailDropDown.Enable="off";
    app.ConfirmButton.Enable="off";
    app.CalculateButton.Enable="on";
end
'''

Sau khi nhấn vào nút Confirm, chương trình sẽ kiểm tra lỗi trong dữ liệu nhập của người dùng, nếu không có lỗi, chương trình sẽ tạo file input.txt dùng để chạy tiếp C++ khi nhấn nút Calculate


## 2.7. Nút PlotGraph

'''
function PlotGraphButtonPushed(app, event)
    app.HeadDropDown.Enable="on";
    app.TailDropDown.Enable="on";
    app.ConfirmButton.Enable="on";

    fig = app.UIFigure;
    data = app.InputTable.Data;                    
         
    Num = round(app.NumofVerticesEditField.Value);                  
                                   
    items = cell(1, Num);
    for i = 1:Num
        items{i} = num2str(i);
    end
    app.HeadDropDown.Items = items;
    app.TailDropDown.Items = items;

                       
    x = str2double(data(:, 1));
    y = str2double(data(:, 2));
    z = str2double(data(:, 3));
            
    numVertices = app.NumofVerticesEditField.Value;

    if app.DirectedButton.Enable == 1
        G = digraph(x, y, z, numVertices);
    elseif app.UndirectedButton.Enable == 1
        G = graph(x, y, z, numVertices);
    end         
                                
    plot(app.UIAxes, G, 'EdgeLabel', G.Edges.Weight);
end
'''

Sau khi nhấn vào nút PlotGraph, chương trình sẽ phát họa được đồ thị (chưa có đường đi ngắn nhất) từ những dữ liệu người dùng nhập trong chương trình.

# 3. Khai báo các tính chất của những thành phần xuất hiện trong app

'''
    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.Position = [100 100 1002 678];
            app.UIFigure.Name = 'MATLAB App';

            % Create Group
            app.Group = uilabel(app.UIFigure);
            app.Group.BackgroundColor = [1 1 1];
            app.Group.HorizontalAlignment = 'center';
            app.Group.FontWeight = 'bold';
            app.Group.Position = [91 641 90 22];
            app.Group.Text = 'CN01 - Nhóm 8';

            % Create Name
            app.Name = uilabel(app.UIFigure);
            app.Name.BackgroundColor = [1 1 1];
            app.Name.HorizontalAlignment = 'center';
            app.Name.WordWrap = 'on';
            app.Name.FontWeight = 'bold';
            app.Name.Position = [383 641 437 22];
            app.Name.Text = 'ĐỀ TÀI 08: THUẬT TOÁN FLOYD - WARSHALL TÌM ĐƯỜNG ĐI NGẮN NHẤT';

            % Create Panel
            app.Panel = uipanel(app.UIFigure);
            app.Panel.TitlePosition = 'centertop';
            app.Panel.Title = 'Panel';
            app.Panel.FontWeight = 'bold';
            app.Panel.Position = [43 44 130 557];

            % Create DirectedButton
            app.DirectedButton = uibutton(app.Panel, 'push');
            app.DirectedButton.ButtonPushedFcn = createCallbackFcn(app, @DirectedButtonPushed, true);
            app.DirectedButton.Position = [14 496 102 23];
            app.DirectedButton.Text = 'Đồ thị có hướng';

            % Create UndirectedButton
            app.UndirectedButton = uibutton(app.Panel, 'push');
            app.UndirectedButton.ButtonPushedFcn = createCallbackFcn(app, @UndirectedButtonPushed, true);
            app.UndirectedButton.Position = [14 457 102 23];
            app.UndirectedButton.Text = 'Đồ thị vô hướng';

            % Create CreateTableButton
            app.CreateTableButton = uibutton(app.Panel, 'push');
            app.CreateTableButton.ButtonPushedFcn = createCallbackFcn(app, @CreateTableButtonPushed, true);
            app.CreateTableButton.BackgroundColor = [0 0.4471 0.7412];
            app.CreateTableButton.Enable = 'off';
            app.CreateTableButton.Position = [15 346 100 23];
            app.CreateTableButton.Text = 'Tạo bảng';

            % Create ResetButton
            app.ResetButton = uibutton(app.Panel, 'push');
            app.ResetButton.ButtonPushedFcn = createCallbackFcn(app, @ResetButtonPushed, true);
            app.ResetButton.BackgroundColor = [1 0 0];
            app.ResetButton.Enable = 'off';
            app.ResetButton.Position = [15 22 100 23];
            app.ResetButton.Text = 'Reset';

            % Create CalculateButton
            app.CalculateButton = uibutton(app.Panel, 'push');
            app.CalculateButton.ButtonPushedFcn = createCallbackFcn(app, @CalculateButtonPushed, true);
            app.CalculateButton.BackgroundColor = [0 1 0];
            app.CalculateButton.Enable = 'off';
            app.CalculateButton.Position = [16 66 100 23];
            app.CalculateButton.Text = 'Tính toán';

            % Create ShngvctLabel
            app.ShngvctLabel = uilabel(app.Panel);
            app.ShngvctLabel.Position = [17 412 51 30];
            app.ShngvctLabel.Text = 'Số cạnh';

            % Create NumofEdgesEditField
            app.NumofEdgesEditField = uieditfield(app.Panel, 'numeric');
            app.NumofEdgesEditField.RoundFractionalValues = 'on';
            app.NumofEdgesEditField.Enable = 'off';
            app.NumofEdgesEditField.Position = [80 416 36 22];

            % Create SnhEditFieldLabel
            app.SnhEditFieldLabel = uilabel(app.Panel);
            app.SnhEditFieldLabel.Position = [17 383 46 22];
            app.SnhEditFieldLabel.Text = 'Số đỉnh';

            % Create NumofVerticesEditField
            app.NumofVerticesEditField = uieditfield(app.Panel, 'numeric');
            app.NumofVerticesEditField.Enable = 'off';
            app.NumofVerticesEditField.Position = [81 383 35 22];

            % Create Label
            app.Label = uilabel(app.Panel);
            app.Label.HorizontalAlignment = 'center';
            app.Label.Position = [2 323 125 22];
            app.Label.Text = '__________________';

            % Create ngicntmLabel
            app.ngicntmLabel = uilabel(app.Panel);
            app.ngicntmLabel.Position = [15 287 102 22];
            app.ngicntmLabel.Text = 'Đường đi cần tìm:';

            % Create uDropDownLabel
            app.uDropDownLabel = uilabel(app.Panel);
            app.uDropDownLabel.Position = [14 250 27 22];
            app.uDropDownLabel.Text = 'Đầu';

            % Create uiDropDownLabel
            app.uiDropDownLabel = uilabel(app.Panel);
            app.uiDropDownLabel.Position = [14 214 30 22];
            app.uiDropDownLabel.Text = 'Đuôi';

            % Create TailDropDown
            app.TailDropDown = uidropdown(app.Panel);
            app.TailDropDown.Items = {''};
            app.TailDropDown.Enable = 'off';
            app.TailDropDown.Position = [67 214 49 22];
            app.TailDropDown.Value = '';

            % Create HeadDropDown
            app.HeadDropDown = uidropdown(app.Panel);
            app.HeadDropDown.Items = {''};
            app.HeadDropDown.Enable = 'off';
            app.HeadDropDown.Position = [67 250 49 22];
            app.HeadDropDown.Value = '';

            % Create Label_2
            app.Label_2 = uilabel(app.Panel);
            app.Label_2.HorizontalAlignment = 'center';
            app.Label_2.Position = [2 149 125 22];
            app.Label_2.Text = '__________________';

            % Create ConfirmButton
            app.ConfirmButton = uibutton(app.Panel, 'push');
            app.ConfirmButton.ButtonPushedFcn = createCallbackFcn(app, @ConfirmButtonPushed, true);
            app.ConfirmButton.BackgroundColor = [0 0.4471 0.7412];
            app.ConfirmButton.Enable = 'off';
            app.ConfirmButton.Position = [15 174 100 23];
            app.ConfirmButton.Text = 'Xác nhận';

            % Create PlotGraphButton
            app.PlotGraphButton = uibutton(app.Panel, 'push');
            app.PlotGraphButton.ButtonPushedFcn = createCallbackFcn(app, @PlotGraphButtonPushed, true);
            app.PlotGraphButton.BackgroundColor = [1 1 0.0667];
            app.PlotGraphButton.Enable = 'off';
            app.PlotGraphButton.Position = [15 111 100 23];
            app.PlotGraphButton.Text = 'Vẽ đồ thị';

            % Create DliuPanel
            app.DliuPanel = uipanel(app.UIFigure);
            app.DliuPanel.TitlePosition = 'centertop';
            app.DliuPanel.Title = 'Dữ liệu';
            app.DliuPanel.FontWeight = 'bold';
            app.DliuPanel.Position = [217 44 308 557];

            % Create InputTable
            app.InputTable = uitable(app.DliuPanel);
            app.InputTable.ColumnName = {'1'; '2'; '3'; '4'};
            app.InputTable.RowName = {'1,2,3,4'};
            app.InputTable.ColumnEditable = true;
            app.InputTable.Position = [33 314 242 205];

            % Create OutputTable
            app.OutputTable = uitable(app.DliuPanel);
            app.OutputTable.ColumnName = {'1'; '2'; '3'; '4'};
            app.OutputTable.RowName = {'1,2,3,4'};
            app.OutputTable.ColumnEditable = true;
            app.OutputTable.CellEditCallback = createCallbackFcn(app, @OutputTableCellEdit, true);
            app.OutputTable.Enable = 'off';
            app.OutputTable.Position = [35 51 240 207];

            % Create MatrnInputLabel
            app.MatrnInputLabel = uilabel(app.DliuPanel);
            app.MatrnInputLabel.HorizontalAlignment = 'center';
            app.MatrnInputLabel.Position = [117 284 76 22];
            app.MatrnInputLabel.Text = 'Ma trận Input';

            % Create MatrnOutputLabel
            app.MatrnOutputLabel = uilabel(app.DliuPanel);
            app.MatrnOutputLabel.HorizontalAlignment = 'center';
            app.MatrnOutputLabel.Position = [111 19 85 22];
            app.MatrnOutputLabel.Text = 'Ma trận Output';

            % Create thPanel
            app.thPanel = uipanel(app.UIFigure);
            app.thPanel.TitlePosition = 'centertop';
            app.thPanel.Title = 'Đồ thị';
            app.thPanel.FontWeight = 'bold';
            app.thPanel.Position = [556 44 415 555];

            % Create UIAxes
            app.UIAxes = uiaxes(app.thPanel);
            app.UIAxes.XTick = [];
            app.UIAxes.YTick = [];
            app.UIAxes.ZTick = [];
            app.UIAxes.Position = [19 104 376 415];

            % Create ShngvctLabel_2
            app.ShngvctLabel_2 = uilabel(app.thPanel);
            app.ShngvctLabel_2.Position = [58 73 245 21];
            app.ShngvctLabel_2.Text = 'Trọng số đường đi ngắn nhất';

            % Create WeightEditField
            app.WeightEditField = uieditfield(app.thPanel, 'numeric');
            app.WeightEditField.RoundFractionalValues = 'on';
            app.WeightEditField.Editable = 'off';
            app.WeightEditField.Position = [320 73 36 22];

            % Create ngingnnhtEditFieldLabel
            app.ngingnnhtEditFieldLabel = uilabel(app.thPanel);
            app.ngingnnhtEditFieldLabel.Position = [58 39 112 22];
            app.ngingnnhtEditFieldLabel.Text = 'Đường đi ngắn nhất';

            % Create ngingnnhtEditField
            app.ngingnnhtEditField = uieditfield(app.thPanel, 'text');
            app.ngingnnhtEditField.Editable = 'off';
            app.ngingnnhtEditField.HorizontalAlignment = 'right';
            app.ngingnnhtEditField.Position = [256 39 100 22];

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end
'''
