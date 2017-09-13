function y  = SymmTropBarCodes_mrm(intervals,m,l,p)

% A function that evaulates a 2-symmetric tropical  rational polynomial on a given
% (1,1)^p(0,1)^l evaluated at x.
% These polynomials constuction comes from
% Verovsek, Sara Kalisnik. "Tropical Cooredinates on the space of
% Persistence Barcodes."
%
% Inputs: intervals corresponds to the bars (b,d) in the barcode, m is the
% parameter used to separate points, l is the exponent on [0,1] and p is
% the exponent on [1,1].
%
% Output: The polynomial evaluated with the given barcode.
%
% Original code by Melissa R. McGuirl, Brown University (Modeled off of code by S.
% Kalisnik- Verovsek). 
%
% Last updated: 12/05/16

% Get all bar lengths and number of bars.
BarLengths = intervals(:,2)-intervals(:,1);
numBars = size(BarLengths,1);

% Store polynomial data [min(b, m*d), d-b] in X variable.
X = zeros(numBars,2);
X(:,1) = min(m*BarLengths(:,1),intervals(:,1));
X(:,2) = BarLengths;


% Add bars of length 0 if l + p > number of bars.
if l + p > numBars
    X(numBars+1:l + p, 1) = 0;
    X(numBars+1:l + p, 2) = 0;
    numBars = l + p;
end


    % If l = 0, p~=0 y is just sum of (min(b, m*d) + d-b) for pth largest sum
if l == 0 && p~= 0
    e_11 = sort(X(:,1) + X(:,2), 'descend');
    y = sum(e_11(1:p));
    
    % If p = 0, l~=0 y is just sum of (min(b, m*d) + d-b) for pth largest sum
elseif l ~= 0 && p== 0
    e_01 = sort(X(:,2), 'descend');
    y = sum(e_01(1:l));
    
    % If  p = l = 0, y = 0.
elseif l== 0 && p == 0
    y = 0;
  
     % If l and p nonzero, take max over all combinations. 
else
    
    I=nchoosek(1:numBars,l);
    y = 0;
    
    for j=1:size(I,1)
        e_01 = sum(X(I(j,:), 2));
        J = nchoosek(setdiff(1:numBars, I(j,:)), p);
        for k = 1:size(J,1)
            e_11 = sum(X(J(k,:),1) + X(J(k,:),2));
            y = max(y, e_01 + e_11);
        end
    end
    
end






end

