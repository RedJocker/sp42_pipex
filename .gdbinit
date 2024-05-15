file ./pipex

set detach-on-fork off
set follow-fork-mode parent

b main
b command_pipe_execute
b command_simple_execute
b command_simple_log_error
b main_bonus.c:34

run here_doc "EOF" "cat" "cmd" output.txt

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
