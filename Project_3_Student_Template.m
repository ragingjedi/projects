% Project 03 Introduction to Computational Physics
% 
% Student name: 
% due date: Wednesday, Oct 17
%
% MATLAB Objectives:
%  1) how to write and work with a script
%  2) how to make good use of comment statements
%  3) how to organize scripts
%  4) how to use the input() function
%  5) how to work with disp() and build a simple menu
%  6) how to check input data for consistency (sanity check)
%  7) how to work with arrays
%  8) how to use the .* functionality of MATLAB
%  9) how to work with loops and nested loops
% 10) how to plot functions and label the graphs
% 11) how to use num2str() function with formating
% 12) how to use logical statements (if-then and switch)
%
% Physics Objectives
% 1) Work with the basic principles of linear superposition of waves
% 2) Work with the propagation of wave fronts (Huygens principle)
% 3) Work with Taylor expansions
% 4) Track interference pattern dependence on relative wavelength scale
% 5) Work with summations as approximation to integrals
% 6) Importance of enforcing symmetry in calculations. 
% 7) experience independence and unstructureness during problem solving
%
% -------------------------------------------------------------- important
% You will be seeing commands in the program I am sending you. Look them
% up, and try to understand their importance. Ask questions about them. 
%
% Using the find feature in MATLAB editor, find all my DO THIS, and spend
% time on understanding the reasons behind the code.   
% ------------------------------------------------------------------------
clear all     % DO THIS. put your mouse over all and read what MATLAB says
              % What is the reason to use clear all?
              % notice that MATLAB gives you warnings (read them!)
              % Often you know more than MATLAB and can ignore warnings. 
close all                  % DO THIS. what is the purpose of this command?
%%                                          Young's double slit experiment
% ------------------------------------------------------- useful constants
convert_nm2mm = 1/1000000;                             % conversion factor
convert_m2mm  = 1000;                                  % conversion factor
% ----------------------------------------------------------- input values
phaseShift1 = 0*180/pi;                                   % Units: radians
phaseShift2 = 0*180/pi;          % Only need 1 phase shift. Units: radians
d = 0.3;                                          % units: milimeters (mm)
a = 0.01;                                                    % units: (mm)
c = 3.0e8;                                     % speed of light: units m/s
window = 5000;                                                        % mm
% ---------------------------------------------- description of the theory
%
%                                                        |    yMAX
%                                                        |
%                                                        |
% 1=                                                     |
%  d - - - - - - - - - - - - - - - - - - - - - - - - - - + - -  picture
% 2=                                                     |
%                                                        |
%                                                        |
%                                                        |   -yMAX
% x=0                                                   x=L
%
% Theory: Applicable for theta small (say less than 30 degrees)
% Theory: d*sin(theta) = m*lambda    for maximum constructive interference
%         sin(theta) ~ tan(theta) = y/L
%      => y(m) = m* (lambda*L/d)
% phaseShift1 = initial phase at slit 1                      (see picture)
% phaseShift2 = initial phase at slit 2                      (see picture)
% intensity = [ sin(phase1 + r1*2*pi/lambda) + ...
%               sin(phase2 + r2*2*pi/lambda)]^2
% ------------------------------------------------------------------------
clc                                                         % clear screen
%%                                                              user input
disp('   ');
disp('1) double slit interference pattern, direct method');
disp('2) double slit interference pattern, small angle approximation');
disp('3) single slit diffraction pattern');
disp('   ');
option = input('Enter option: ');
  switch option
    case {1,2}
    disp(['distance between two slits = ',num2str(d),' mm']);
    case 3
    disp(['range of slit width this program will handle: ', ...
      '0.001 < a < 0.02 mm']);
    a = input('Enter width of single slit in mm: ');                % (mm)
    otherwise
    error('unknown option');
  end
L = input('Enter distance between slits and screen in m: ');         % (m)
  if( option < 3 )
  window = input('Enter maximum observation window in mm: ');       % (mm)
  end
disp(['range of wavelength this program will handle: ', ...
      '1 nm < lambda < 100000 nm']);
lambda = input('Enter wavelength of light in nm: ');   % units: nanometers
       % ^^^^^------> DO THIS use help on input and read its documentation
% ----------------------------------------------------------- sanity check
   if( lambda < 1 )
   error('1nm is to short of a wavelength');
   end
   if( lambda > 100000 )
   error('100000 nm is to long of a wavelength');
   end
   if( L*convert_m2mm < 25*d )
   error('L is to small for the distance between slits: L >> d');
   end
   if( L*convert_m2mm > 10000000*d )
   error('Although L >> d, this is a bit too much!');
   end
windowMax = 100*(lambda*convert_nm2mm)*(L*convert_m2mm)/d;   % units: (mm)
windowMin = 0.1*(lambda*convert_nm2mm)*(L*convert_m2mm)/d;   % units: (mm)
window = max( min(window,windowMax), windowMin);     % => reasonable range
%      % ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ DO THIS. Explain what this
%        code is doing? 
%
% DO THIS: I am using window as a variable. Some of you might note that
%          window is a MATLAB package depending on what modules you 
%          installed. As a general question, is it proper to override the
%          name of a MATLAB function and use that same name as a variable
%          within your script or program? What would be the conseqences? 
%
yMAX0 = window/2; 
   if( a < 0.001 )
   error('width of single slit is too small');
   end
   if( a > 0.02 )
   error('width of single slit is too large');
   end
%%                                calculate predicted interference pattern
% ----------------------------------------------- get range of calculation
T = (lambda/c)*1000000;                     % period in femto-seconds (fs)
yMAX = 5*(lambda*convert_nm2mm)*(L*convert_m2mm)/d;          % units: (mm)
YMAX = min(yMAX,yMAX0);
yMIN = -yMAX;                                                % units: (mm)
dy = (yMAX - yMIN)/2000;             % ~ about 2000 points will be plotted
y = yMIN:dy:yMAX;               % domain of observation: see picture above
L2 = (L*convert_m2mm)^2;
r1 = sqrt( (y - d/2).^2 + L2 );             % top slit (see picture above)
r2 = sqrt( (y + d/2).^2 + L2 );             % top slit (see picture above)
%                   ^^^----> DO THIS, make sure you understand .^ operator
op1 = phaseShift1 + 2*pi*r1/(lambda*convert_nm2mm); % end phase for path 1
op2 = phaseShift2 + 2*pi*r2/(lambda*convert_nm2mm); % end phase for path 2
yPts = length(y);
%%                                 interference: method 1: direct approach
% ------------------------------------------------------------------------
% WORTH 10% of the grade  (Answering these three questions)
% 1) Look over this code, and make sure you do all of the DO THIS. Try to 
%    understand the purpose of each part of the code and know what each
%    part is doing. Plan on making use of parts of this code for the 
%    remainder of the project (next two parts).
% 2) Run this first section many times. Your goal is to understand what is
%    happening for fixed d, in the case that the wavelength of light 
%    (lambda) is very small, small, large, and very large --- relatively
%    speaking. Take note on how the dynamic part of the output depends on
%    your inputs (the setup of the problem).
% 3) Contrast how the time average result changes compared to the dynamic
%    part. Does this phenomena make sense physically. Which part does and
%    which part does not. 
% Write your answers here:
%
%
% ------------------------------------------------------------------------
% {
if( option == 1 )
phase = 0:0.01:2*pi;                      % used for making a time average
zPts = length(phase);
amplitudeArray = zeros(zPts,yPts);                           % preallocate
                %^^^^^^^^^^^^^^^^ DO THIS. This is a two dimensional array
                %                 What does preallocate mean? 
                %                 Why am I doing this here?
                %                 Why did I decide to make this 2D array?
  for j=1:zPts
  amplitudeArray(j,:) = sin( phase(j) + op1 ) + sin( phase(j) + op2 ); 
  end
intensity = mean( amplitudeArray.^2 );
                              % ^^^----> DO THIS, learn what this is doing
% ------------------------ show time dependence of instantaneous intensity
dPhase = 2*pi/50;
phaseMax = 5*(2*pi);                                           % 5 periods
   for phase=0:dPhase:phaseMax
   t = T*phase/(2*pi);
   a = sin( phase + op1 ) + sin( phase + op2 );
   a2 = a.*a;                                    % instantaneous intensity
       % ^^----------------------------> DO THIS, learn what this is doing
   %b = sin( phase ) + sin( phase + op1 - op2 );
   %b2 = b.*b;
% -------------------------------------------------------------- plot data
   figure(1);  % DO THIS. Notice you can put a number to identify a figure
               % Explain why one might want to do this.
   clf         % DO THIS. What is the clf command doing?
   hold on;
   plot(y,a2,'r','linewidth',0.7);                               % dynamic
   %plot(y,b2,'b','linewidth',1.2);                              % dynamic
   plot(y,intensity,'k','linewidth',1.8);
   xlabel('position (mm)');
   ylabel('intensity (AU)');
   title(['interference pattern: L= ',num2str(L),' m', ...
          ' lambda= ',num2str(lambda),' nm', ...
          ' time= ',num2str(t,'%2.4f'),' fs']); 
   legend('instantaneous','time averaged');
   ylim( [0,4] );
   pause(0.2);
   end
end
%}
%%                                   interference: method 2: Taylor expand
% ------------------------------------------------------------------------
% WORTH 50% of the grade
% 1) Following the structure of the above code, do the same calculation
%    but use Taylor expansions to figure out phase differences. Write the
%    necessary code in place of the 'not implemented' statement. 
% 2) Compare the results from the direct method and this method. Determine
%    which of the two methods is more accurate and explain why. 
% 3) Explain why the time average is being performed. Is this being 
%    measured or is this just a convienent way to summarize the data?
%
% GIVE your answers to (2) and (3) here, with your explanations for why. 
%
%
%
%
% ------------------------------------------------------------------------
% {
if( option == 2 )
error('not implemented yet');
end
%} 
%%                            calculate diffraction pattern of single slit
% ------------------------------------------------------------------------
% WORTH 30% of the grade
% Represent a single slit as a finite number of source points according to
% Huygens princple. This number can be adjusted. Using this finite number
% of source points to represent the source from the single slit, employ
% linear superpositon, and from these calculations predict the diffraction
% pattern using the time-averaged intensity profile. Do this for a varying
% number of points, and show how the answer depends on the number that you
% selected to use. Then after coding this up, answer these questions here.
%
% 1) How are you to determine how many points you should use to represent 
%    the wavefront accurately? 
% 2) Did you consider symmetry when selecting where to place the wavefront
%    sources along the slit width? Explain why this is important. 
%
%
% ------------------------------------------------------------------------
% {
if( option == 3 )
error('not implemented yet');
end
%}
% ------------------------------------------------------------------------
% WORTH 10% of the grade
% Calculate the diffraction pattern from 1 slit like you did in the above
% problem, but this time, randomize the locations of the Huygens source
% points. Compare the answer you get using a random selection, versus the
% set pattern you used that preserves mirror symmetry in the vertical 
% direction. Comment about the difference in approach/results.
% Answer here:
%
%
%
% ------------------------------------------------------------------------






