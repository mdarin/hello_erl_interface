-module(enode).
-export([start/0, stop/0, init/0, loop/0]).


start() ->
	spawn('en1@127.0.0.1', ?MODULE, init, []).
stop() ->
	{any, 'en1@127.0.0.1'} ! stop.

init() ->
	register(resolver, self()),
	loop(),
	{any, 'en1@127.0.0.1'} ! {call, 2, self()}.


loop() ->
	receive
		{call, Arg, From} ->
			{any, 'en2@127.0.0.1'} ! {reply, {res, Arg, From}},
			loop();
		stop ->
			{'EXIT', noraml}
	end.
	
