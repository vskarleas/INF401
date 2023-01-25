touch ~/.bashrc
grep "401infrc.sh" ~/.bashrc > /dev/null 2>&1 || echo "source /Public/401_INF_Public/etc/401infrc.sh" >> ~/.bashrc
grep ".bashrc" ~/.bash_profile > /dev/null 2>&1 || echo "source ~/.bashrc" >> ~/.bash_profile
source /Public/401_INF_Public/etc/401infrc.sh
