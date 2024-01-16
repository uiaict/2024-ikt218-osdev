import requests
import pathlib
import logging
from flask import Flask, render_template

# Setup logger
_LOGGER = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

# Define paths
current_dir = pathlib.Path(__file__).parent
static_dir = current_dir.joinpath("static")
os_dir = static_dir.joinpath("os")

# Create necessary directories
static_dir.mkdir(exist_ok=True)
os_dir.mkdir(exist_ok=True)

def download_v86():
    URL_BASE = "https://github.com/copy/v86/releases/download/latest/"
    FILES = ["libv86.js", "v86.wasm"]

    for file_name in FILES:
        file_path = static_dir.joinpath(file_name)
        if not file_path.exists():
            _LOGGER.info(f"{file_path} does not exist. Downloading...")
            resp = requests.get(URL_BASE + file_name)
            if resp.status_code == 200:
                with file_path.open("wb") as f:
                    f.write(resp.content)
                _LOGGER.info(f"{file_path} download was successful.")
            else:
                _LOGGER.error(f"Failed to download {file_path}. Status code: {resp.status_code}")
        else:
            _LOGGER.info(f"{file_path} exists. Skipping download")

if __name__ == "__main__":
    download_v86()

    app = Flask(__name__, static_url_path='', static_folder=static_dir)

    @app.route('/')
    @app.route('/index')
    def index():
        os_list = [file.name for file in os_dir.glob("*.img") + os_dir.glob("*.bin")]
        return render_template('index.html', os_list=os_list)

    app.run(debug=True)
