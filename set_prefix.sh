export GNUARMDIR=/opt/gnu/arm
export PREFIX=`find ${GNUARMDIR} -maxdepth 1 -type d | grep arm- | sed -e "s!${GNUARMDIR}/!!"`-

