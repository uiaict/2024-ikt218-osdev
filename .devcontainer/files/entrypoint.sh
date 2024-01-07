#!/bin/bash
# Start supervisord in the background and redirect its output to /dev/null

# open supervisord in tmux
tmux new-session -d -s supervisord
tmux send-keys -t supervisord "/usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf" C-m

# End of entrypoint
# -----------------
