import subprocess

def cmd_exists(cmd):
    return subprocess.call("type " + cmd, shell=True,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0