# follow these steps to build permute from scratch:

# first, make sure that all of the prerequisits are installed:
sudo apt-get update
sudo apt-get install build-essential libc6-dev autoconf automake libtool gettext autotools-dev git 

# add the following to your ~/.gitconfig file:
$ git config --global user.name "your first and last name"
$ git config --global user.email "your-email@your-email-provider"

# download and build permute form source:
mkdir ~/src
cd ~/src
git clone https://github.com/dad98253/permute.git
cd permute
autoreconf -i -f
./configure
make
make check

# to install locally, enter the following (this installs in /usr/local/bin):
sudo make install

# ---------------------------------------------------------------------------------------

# if you plan to build a debian package file, you will also need the following:
sudo apt-get install debmake devscripts dh_autoreconf autopkgtest dpkg quilt lintian
sudo apt-get install gpg gpg-agent sbuild schroot ccache libeatmydata1 parallel 
sudo apt-get install sbuild-debian-developer-setup git-buildpackage

# also, set the following to your ~/.bashrc file:
DEBEMAIL="your-email@your-email-provider"
DEBFULLNAME="your first and last name"
export DEBEMAIL DEBFULLNAME
alias dquilt="quilt --quiltrc=${HOME}/.quiltrc-dpkg"
. /usr/share/bash-completion/completions/quilt
complete -F _quilt_completion $_quilt_complete_opt dquilt

# create ~/.quiltrc-dpkg and add the following to it:
d=.
while [ ! -d $d/debian -a `readlink -e $d` != / ];
do d=$d/..; done
if [ -d $d/debian ] && [ -z $QUILT_PATCHES ]; then
QUILT_PATCHES="debian/patches"
QUILT_PATCH_OPTS="--reject-format=unified"
QUILT_DIFF_ARGS="-p ab --no-timestamps --no-index --color=auto"
QUILT_REFRESH_ARGS="-p ab --no-timestamps --no-index"
QUILT_COLORS="diff_hdr=1;32:diff_add=1;34:diff_rem=1;31:diff_hunk=1;33:"
QUILT_COLORS="${QUILT_COLORS}diff_ctx=35:diff_cctx=33"
if ! [ -d $d/debian/patches ]; then mkdir $d/debian/patches; fi
fi

# if you don't have one, generate a gpg key:
gpg --gen-key --default-new-key-algo=rsa4096/cert,sign+rsa4096/encr

# create ~/.devscripts and add the following to it:
DEBUILD_DPKG_BUILDPACKAGE_OPTS="-i -I -us -uc"
DEBUILD_LINTIAN_OPTS="-i -I --show-overrides"
DEBSIGN_KEYID="Your_GPG_keyID_from_above"

sudo sbuild-debian-developer-setup -s unstable

# create ~/.sbuildrc and do the following to add to it:
cat >~/.sbuildrc << 'EOF'
##############################################################################
# PACKAGE BUILD RELATED (source-only-upload as default)
##############################################################################
# -d
$distribution = 'unstable';
# -A
$build_arch_all = 1;
# -s
$build_source = 1;
# --source-only-changes
$source_only_changes = 1;
# -v
$verbose = 1;
##############################################################################
# POST-BUILD RELATED (turn off functionality by setting variables to 0)
##############################################################################
$run_lintian = 1;
$lintian_opts = ['-i', '-I'];
$run_piuparts = 1;
$piuparts_opts = ['--schroot', 'unstable-amd64-sbuild'];
$run_autopkgtest = 1;
$autopkgtest_root_args = '';
$autopkgtest_opts = [ '--', 'schroot', '%r-%a-sbuild' ];
##############################################################################
# PERL MAGIC
##############################################################################
1;
EOF

#set up a dedicated persistent chroot “source:unstable-amd64-desktop” by (example for amd64 arch):
$ sudo cp -a /srv/chroot/unstable-amd64-sbuild /srv/chroot/unstable-amd64-desktop
$ sudo tee /etc/schroot/chroot.d/unstable-amd64-desktop << EOF
[unstable-amd64-desktop]
description=Debian sid/amd64 persistent chroot
groups=root,sbuild
root-groups=root,sbuild
profile=desktop
type=directory
directory=/srv/chroot/unstable-amd64-desktop
union-type=overlay
EOF

# You should now be able to log into this chroot by:
$ sudo schroot -c source:unstable-amd64-desktop
# (enter exit to return)

# create ~/.gbp.conf and add the following to it:
[DEFAULT]
# the default build command:
builder = sbuild
# use pristine-tar:
pristine-tar = True
# Use color when on a terminal, alternatives: on/true, off/false or auto
color = auto


# to build the debian package file, enter the following
./dodeb.sh

# the .deb file will be created in ~/src
# to install from the .deb file (note that this will install in /usr/bin , not /usr/local/bin):

sudo dpkg -i ~/src/permute_0.2-1_amd64.deb	# (on intel based PCs)
# or
sudo dpkg -i ~/src/permute_0.2-1_armhf.deb	# (on ARM based computers)

