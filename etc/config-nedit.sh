if [ ! -f $HOME/.nedit ]; then
   # le fichier .nedit n'existe pas
   if [ -d $HOME/.nedit ]; then
      # mais il existe un repertoire de ce nom
      mv $HOME/.nedit $HOME/.nedit.`date +%y%m%d%H%M%S`
   fi
   cp /Public/401_INF_Public/etc/neditrc $HOME/.nedit
else
   # un fichier .nedit existe deja
   if diff /Public/401_INF_PUBLIC/etc/neditrc $HOME/.nedit >/dev/null 2>&1; then
      # il s'agit du fichier fourni pour les tp de programmation
      echo >/dev/null 2>&1
   else
      # ce n'est pas le fichier fourni pour les tp de programmation
      mv $HOME/.nedit $HOME/.nedit.`date +%y%m%d%H%M%S`
      cp /Public/401_INF_PUBLIC/etc/neditrc $HOME/.nedit
   fi
fi

