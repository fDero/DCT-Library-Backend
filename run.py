import os
import platform
import subprocess
import sys

def run_script(script_path):
    try:
        subprocess.run(script_path, check=True, shell=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running script: {e}")

def main():
    if len(sys.argv) != 2:
        print("Usage: python run.py <script_name>")
        sys.exit(1)

    script_name = sys.argv[1]
    script_path_unix = os.path.join(os.path.dirname(__file__), "scripts/unix", f"{script_name}.sh")
    script_path_windows = os.path.join(os.path.dirname(__file__), "scripts/windows", f"{script_name}.bat")

    if platform.system() in ["Linux", "Darwin"]:
        if os.geteuid() == 0:
            run_script(f"sudo {script_path_unix}")
        else:
            run_script(script_path_unix)
    elif platform.system() == "Windows":
        if os.name == "nt" and os.environ.get("ADMIN_PRIVILEGES") == "1":
            run_script(f"runas /user:Administrator /savecred {script_path_windows}")
        else:
            run_script(script_path_windows)
    else:
        print("Unsupported operating system")

if __name__ == "__main__":
    main()
