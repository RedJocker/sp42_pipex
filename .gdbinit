file ./pipex

set detach-on-fork off
set follow-fork-mode parent

b main
b command_pipe_execute
b command_simple_execute

run input.txt "./a.out" "./a.out" "./a.out" output.txt && cat output.txt

define pcmd
  if $arg0->type == SIMPLE
    printf "Simple(%s)\n", $arg0->debug_id
	printf "input: "
	p $arg0->input
	printf "output: "
	p $arg0->output
	printf "close: "
	p $arg0->close
  else
	if $arg0->type == PIPE
	  printf "Pipe(%s)\n", $arg0->debug_id
	  printf "input: "
	  p $arg0->input
	  printf "output: "
	  p $arg0->output
	  printf "close: "
	  p $arg0->close
	  printf "Before"
	  pcmd $arg0->pipe->before
	  printf "After"
	  pcmd $arg0->pipe->after
	end
  end
   
end
