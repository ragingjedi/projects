% Project 02 Introduction to Computational Physics
% 
% Student name: 
% due date: Oct 3
%
% MATLAB Objectives:
% 1) how to write and work with a script
% 2) how to work with arrays
% 3) how to plot functions
% 4) how to use the .* functionality of MATLAB
% 5) how to organize scripts
% 6) how to work with disp() and labeling figures
%
% Physics Objectives
% 1) Understand the general solution to a simple wave equation
% 2) Simulate the principle of superposition in 1D w.r.t. traveling waves
% 3) Work with sinusoidal traveling waves
% 4) Work with Gaussian wavepackets from the standard wave equation
% 5) Work with a quantum Gaussian wavepacket
% 6) Compare dispersion in quantum vs. classical Gaussian wavepackets
%
% wave equation:  F_tt = v^2 * F_xx    Solution: F(x,t) --> F(x +/- vt)
%
% quantum Gausian wavepacket solves the Schrodinger equation.
% The partial diff. Eq. ==>    i hbar psi_t = - (hbar^2)/(2*m) psi_xx
clear all
close all
%%                             add two traveling sinusoidal waves together
% WORTH 40% of the grade
%{
% ------------------------------------------------------ sinusoidal wave 1
lambda1 = 3;                                    % wavelength units (meter)
T1 = 0.5;                                          % period units(seconds)
A1 = 1;                                      % amplitude (arbitrary units)
phi1 = pi/2;                                % phase offset units (radians)
% ------------------------------------------------------ sinusoidal wave 2
lambda2 = 4;
T2 = 2; 
A2 = 2;
phi2 = 0;
% ---------------------------------------------------- dependent variables
k1 = 2*pi/lambda1;
k2 = 2*pi/lambda2;
omega1 = 2*pi/T1;
omega2 = 2*pi/T2;
% --------------------------------
dx = min(lambda1,lambda2)/100;
dt = min(T1,T2)/100;
xMax = 5*max(lambda1,lambda2);
xMin = -xMax;
tMin = 0;
tMax = 5*max(T1,T2);
x = xMin:dx:xMax;
nMax = ceil(tMax/dt);
% ---------------------------------------------------- make the simulation
   for n=0:nMax
   t = dt*n;
% ------------------------------------------------------- do superposition
   y1 = A1*sin( k1*x - omega1*t + phi1 );
   y2 = A2*sin( k2*x - omega2*t + phi2 );
   yTotal = y1 + y2;
% ----------------------------------------------------------- plot results
   plot(x,yTotal,'b','linewidth',1.5);
   xlabel('position (m)');
   ylabel('superposition (AU)');
      if( 100*floor(n/100) == n )
      title(['time = ',num2str(t),' seconds']);
      pause(1.5);
      else
      pause(0.001);
      end
   end
%}
%%                             add  m  traveling sinusoidal waves together
% WORTH 25% of the grade
%{
lambdaArray = [0.5, 1.0, 2.0, 4.0, 8.0, 16.0];   % wavelength units (meter)
periodArray = [1.0, 1.0, 1.0, 1.0, 1.0,  1.0];     % period units (seconds)
ampArray    = [1.0, 1.0, 1.0, 1.0, 1.0, 1.0];   % amplitude arbitary units
phaseArray  = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]*pi;      % unitless (radians)
dirArray    = [ 1,   1, -1,  -1,   1,   1 ];    % (left/right) directions
m1 = length(lambdaArray);
m2 = length(periodArray);
m3 = length(ampArray);
m4 = length(phaseArray);
m5 = length(dirArray);
% -------------------------------------------- check for input consistency
   if( m1 ~= m2 )
   error('lambdaArray length not equal to periodArray length');
   end
   if( m1 ~= m3 )
   error('lambdaArray length not equal to ampArray length');
   end
   if( m1 ~= m4 )
   error('lambdaArray length not equal to phaseArray length');
   end
   if( m1 ~= m5 )
   error('lambdaArray length not equal to dirArray length');
   end
% ---------------------------------------------------- dependent variables
waveNum = (2*pi)./lambdaArray;
omega = 2*pi*dirArray./periodArray;    % includes direction of propagation
% ------------------------------------------------------------------------
dx = min(lambdaArray)/100;
dt = min(periodArray)/100;
xMax = 5*max(lambdaArray);
xMin = -xMax;
tMin = 0;
tMax = 5*max(periodArray);
x = xMin:dx:xMax;
nMax = ceil(tMax/dt);
npts = length(x);
yTotal = zeros(1,npts);                                     % preallocate!
   for n=0:nMax
   t = dt*n;
% ------------------------------------------------------- do superposition
   yTotal = 0*yTotal;
      for j=1:m1
      y = ampArray(j)*sin( waveNum(j)*x - omega(j)*t + phaseArray(j) );
      yTotal = yTotal + y;
      end
% ----------------------------------------------------------- plot results
   plot(x,yTotal,'b','linewidth',1.5);
   xlabel('position (m)');
   ylabel('superposition (AU)');
   ylim( [-12,12] );
      if( 100*floor(n/100) == n )
      title(['time = ',num2str(t),' seconds']);
      pause(1.5);
      else
      pause(0.001);
      end
   end
%}
%%                         add two traveling Gaussian wavepackets together
% WORTH 20% of the grade
%{
% ------------------------------------------------------- Gaussian pulse 1
lambda1 = 3;                                    % wavelength units (meter)
T1 = 0.5;                                          % period units(seconds)
A1 = 1;                                      % amplitude (arbitrary units)
phi1 = pi/2;                                % phase offset units (radians)
width1 = 2*lambda1;      % standard deviation of a Gaussian units (meters)
x1o = -1*width1;             % center of wave packet at t=0  units (meter)
dir1 = 1;                                            % moving to the right
% ------------------------------------------------------- Gaussian pulse 2
lambda2 = 2;
T2 = 2; 
A2 = 1;     % also try -1
phi2 = 0;
width2 = 2*lambda2;
x2o = 4*width2 - 3*width1;
dir2 = -1;
% ---------------------------------------------------- dependent variables
k1 = 2*pi/lambda1;
k2 = 2*pi/lambda2;
omega1 = dir1*2*pi/T1;
omega2 = dir2*2*pi/T2;
v1 = omega1/k1;
v2 = omega2/k2;                                  % set moving to the left
% --------------------------------
dx = min(lambda1,lambda2)/100;
dt = min(T1,T2)/50;
xMax = 5*max(lambda1,lambda2);
xMax = 3*xMax + 10*max(x1o,x2o) + 90;
x1o = x1o - 20;
x2o = x2o + 20;
xMin = -xMax + min(x1o,x2o) + 90;
tMin = 0;
tMax = 10*max(T1,T2);
x = xMin:dx:xMax;
nMax = ceil(tMax/dt);
% ---------------------------------------------------- make the simulation
figure(1);
clf;
   for n=0:nMax
   t = dt*n;
% ------------------------------------------------------- do superposition
   mu1 = x1o + v1*t;                      % location of center of packet 1
   mu2 = x2o + v2*t;                      % location of center of packet 2
   %disp( [mu1,mu2] );
   B1 = A1*normpdf(x,mu1,width1);
   B2 = A2*normpdf(x,mu2,width2);
   y1 = B1.*sin( k1*(x - x1o) - omega1*t + phi1 );
   y2 = B2.*sin( k2*(x - x2o) - omega2*t + phi2 );
   yTotal = y1 + y2;
% ----------------------------------------------------------- plot results
   plot(x,yTotal,'b','linewidth',1.5);
   xlabel('position (m)');
   ylabel('superposition (AU)');
   ylim( [-0.170001, 0.170001] );
      if( 100*floor(n/100) == n )
      title(['time = ',num2str(t),' seconds']);
      pause(1.5);
      else
      pause(0.001);
      end
   end
%}
%%           simulate a single Gaussian wave packet for a quantum particle
% WORTH 15% of the grade
%{
% ---------------------------------- initialization of Gaussian wavepacket
hbar = 4.14/(2*pi);                                 % dimension is (eV*fs)
c = 3000;                                  % speed of light in Angstrom/fs
eEnergy = 510990.6;                        % rest energy of electron in eV
eMass = eEnergy/c^2;                         % in units of (fs^2)*eV/Ang^2
vo = 10.0;                    % initial speed of wavepacket in Angstrom/fs
mass = eMass*1;               % mass of particle in units of electron mass
KE = 0.5*mass*vo*vo;                           % kinetic energy units (eV)
omega = KE/hbar;                          % angular frequency units (1/fs)
lambda = omega/vo;                     % de Broglie wavelength units (Ang)
ko = 2*pi/lambda;
sigX = 2.0;            % reasonable value relative to rpv in units of Ang
disp(['                 mass = ',num2str(mass/eMass),' electron mass']);
disp(['                   vo = ',num2str(vo),        ' Ang/fs'  ]);
disp(['                   KE = ',num2str(KE),        ' ev'  ]);
disp(['                 sigX = ',num2str(sigX),      ' Ang'     ]);
disp(['    angular frequency = ',num2str(omega),     ' 1/fs'     ]);
disp(['de Broglie wavelength = ',num2str(lambda),    ' Ang'     ]);
% --------------------------------------------- define scope of simulation
T = 2*pi/omega;
tMin = 0;
tMax = 5*T;  % try 0.5*T, 2*T, 5*T;
dt = T/100;
nMax = ceil(tMax/dt);
dx = min(lambda,sigX)/50;
xo = 0;                                   % initial location of wavepacket
xMax = xo + vo*tMax + 25*sqrt(tMax)*sigX; 
xMin = xo - 10*sqrt(tMax)*sigX;
x = xMin:dx:xMax;
a = 1/(2*sigX*sigX);                                  % units of 1/Ang^2
%error('stop here for now');
figure(1)
clf;  
   for n=0:nMax
   t = tMin + dt*n;
% ---------------------------------------------- construct the wave packet
%                  See pages 61,77,78 3rd edition: Griffiths and Schroeter
   g0 = 1 + 2*1i*hbar*a*t/mass;        % (eV*fs/Ang^2)*fs/((fs^2)*eV/Ang^2)
   gamma0 = sqrt(g0);
   tempA = (2*a/pi)^0.25;
   x0 = xo + vo*t;
   xx0 = xo + 0.5*vo*t;
   temp0 = ( - a*( x - x0 ).^2 )/g0;
   psi0 = (tempA/gamma0)*exp(temp0 + 1i*ko*(x - xx0) );     % wavefunction
   prob = abs(psi0).^2;                  % probability of finding particle
% ----------------------------------------------------------- plot results
   subplot(3,1,1);
   plot(x,prob,'k','linewidth',1.5);
   xlabel('position (m)');
   title('probability density (1/Ang)');
   %ylim( [-0.5,0.5] );
% ------------------------------------------------------------------------
   subplot(3,1,2);
   realPsi0 = real(psi0);
   plot(x,realPsi0,'b','linewidth',1.5);
   xlabel('position (m)');
   title('real part of wavefunction (1/Ang)');
   %ylim( [-0.5,0.5] );
% ------------------------------------------------------------------------
   subplot(3,1,3);
   imagPsi0 = imag(psi0);
   plot(x,imagPsi0,'r','linewidth',1.5);
   xlabel('position (m)');
   title('imaginary part of wavefunction (1/Ang)');
   %ylim( [-0.5,0.5] );
% % %       if( 100*floor(n/100) == n )
% % %       subplot(3,1,1);
% % %       pause(1.5);
% % %       else
% % %       pause(0.001);
% % %       end
   pause(0.01);
   end     
%}


