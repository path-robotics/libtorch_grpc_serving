python3 -m venv ./venv
source venv/bin/activate
pip3 install --upgrade pip
pip3 install torch==1.2.0+cpu torchvision==0.4.0+cpu -f https://download.pytorch.org/whl/torch_stable.html
pip3 install grpcio-tools

