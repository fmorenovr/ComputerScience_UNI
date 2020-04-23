numTest = 3; % Numero de observaciones para el tests

% Training model:
X0Train = X0(1:end-numTest,:);
y0Train = y0(1:end-numTest);
M0Train = fitlm(X0Train,y0Train);

% Test set:
X0Test = X0(end-numTest+1:end,:);
y0Test = y0(end-numTest+1:end);

% Forecast errors:
y0Pred = predict(M0Train,X0Test);
DiffPred = y0Pred-y0Test;
DiffBase = y0Pred-y0(end-numTest);

% Forecast comparison:
RMSEPred = sqrt((DiffPred'*DiffPred)/numTest)
RMSEBase = sqrt((DiffBase'*DiffBase)/numTest)
