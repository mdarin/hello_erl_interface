% using long node names
-module(veil).
-export([foo/1, bar/1, square/0]).
%% вот так сконнектилось
% $ cd /path/to/dir/veil.beam
% $ erl -name enode@127.0.0.1 -setcookie cookie
% >net_kernel:hidden_connect_node('cnode@127.0.0.1').
% >net_kernel:disconnect('cnode@127.0.0.1').

foo(X) ->
	io:format("~p:foo(~p)~n", [?MODULE, X]),
	call_cnode({foo, X}).
bar(Y) ->
	io:format("~p:bar(~p)~n", [?MODULE, Y]),
	call_cnode({bar, Y}).
square() ->
	call_cnode({square, 0}).

call_cnode(Msg) ->
    {any, 'cnode@127.0.0.1'} ! {call, self(), Msg},
    receive
			{cnode, Result} ->
				Result
    end.

