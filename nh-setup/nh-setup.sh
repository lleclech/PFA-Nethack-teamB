#!/bin/sh

nhdir="nethack-3.4.3/"
nharchive="nethack-343-src.tgz"
dlurl="http://downloads.sourceforge.net/project/nethack/nethack/3.4.3/nethack-343-src.tgz"
patchdir="../patches"
pfadir="../pfa-src"

dl_nethack () {
    if [ ! -e $nharchive ]; then
        read -p "$nharchive not found, automatically download it now? [Y/n]" yn

        case $yn in
            Y|y|"" ) wget $dlurl && apply_patch;;
            * ) exit;;
        esac
    fi

    echo "Extracting... "
    tar -xf $nharchive
    echo "Running NetHack's setup script... "
    cd $nhdir
    sh sys/unix/setup.sh
    cd ..
    patch -p0 < linux_install.patch
    echo "Applying patches... "
    for i in `ls $patchdir`; do
        patch -p2 < $patchdir/$i;
    done
}


if [ -d $nhdir ]; then
    read -p "Use existing $nhdir ? [Y/n]" yn

    case $yn in
        Y|y|"" ) reuse=1;;
        N|n ) rm -rf $nhdir; dl_nethack;;
        * ) echo "please answer 'y' or 'n'"; exit;;
    esac
else
    dl_nethack
fi


#if [ -e $nh ]; then
#    read -p "previous nethack installation found at $nh, overwrite? [y/n]" yn
#
#    case $yn in
#        Y|y ) ;;
#        N|n ) exit;;
#        * ) echo "please answer 'y' or 'n'"; exit;;
#    esac
#fi

cd $pfadir && make pfa

if [ $? = 0 ]; then
	echo ""
	echo "************************************************"
    echo "Nethack run script installed in $nhdir"
fi
