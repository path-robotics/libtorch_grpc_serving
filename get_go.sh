wget https://storage.googleapis.com/golang/go1.12.9.linux-amd64.tar.gz
sudo tar -C /usr/local -xzf go*linux-amd64.tar.gz
echo 'export PATH=$PATH:/usr/local/go/bin' >> $HOME/.bashrc
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib' >> $HOME/.bashrc
source $HOME/.bashrc
