# Gestion des chemins d'accès aux binaires

source /Public/401_INF_Public/set_prefix.sh
export PATH=/Public/401_INF_Public/bin:${GNUARMDIR}/bin:${PATH}

export TERM=xterm

alias gcc='gcc -Wall -pedantic'

alias a2ps='a2ps -s 2 -A fill -M Letter'

# L'editeur pour le mail avec mutt
#sh /Public/INF401_INF_Public/etc/config-nedit.sh
export EDITOR=${EDITOR:-nedit}

if [ ! -e "$HOME/Mail" ]
then
  mkdir $HOME/Mail
fi

alias mailx='(echo "Utiliser mutt avec ce mode d emploi"; cat /Public/INF401_INF_Public/etc/mutt_help.txt) | more'

# Impression
export PRINTER=IMPRESSION-UGA
export LPDEST=IMPRESSION-UGA

