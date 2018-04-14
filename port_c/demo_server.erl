%% пример из книжки по эрлангу
%% реализация порта erlang <-stdI/O-> c
%% 
%%
%%Usage:
%Running the program we obtain the following:
% > demo_server:start().
%   erlang received from port:{data,[10,2,4,6,8,10]}
%   erlang received from port:{data,[111,104,99,101]}
%   true

-module(demo_server).
-export([start/0]).

%% the connected process for the port
start() ->

	%% Opening ports. 
	%Ports can be opened with a number of different settings.
	Port = open_port({spawn, demo_server}, [{packet, 2}]),

  %% sender
	%%
	%Only three messages are understood by a port:
	%Port ! {PidC, {command, Data}}
	%Port ! {PidC, {connect, Pid1}}
	%Port ! {PidC, close}
	%PidC must be the Pid of the connected process. 
	Port ! {self(), {command, [1,2,3,4,5]}},
	Port ! {self(), {command, [10,1,2,3,4,5]}},
	Port ! {self(), {command, "echo"}},
	Port ! {self(), {command, "abc"}},
	
	read_replies(Port).

%% receiver
%% 
read_replies(Port) ->
	receive
		{Port, Any} ->
			io:format("erlang received from port:~w~n", [Any]),
			read_replies(Port)
		after 2000 ->
			Port ! {self(), close},
				receive
					{Port, closed} ->
													true
				end
		end.
