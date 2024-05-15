file ./pipex

set detach-on-fork off
set follow-fork-mode parent

b main
b command_pipe_execute
b command_simple_execute
b command_simple_log_error
b io_handle_heredoc_to_fd
b main_bonus.c:34

run here_doc "EOF" "cat" "cat" output.txt

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

define pio
  p $arg0->type
  if ($arg0->type == FD)
	p $arg0->fd
  end
  if ($arg0->type == PATH)
	p $arg0->path
	p $arg0->flags
	p $arg0->mode
  end
  if ($arg0->type == HEREDOC)
	p $arg0->heredoc_limiter
  end
end
