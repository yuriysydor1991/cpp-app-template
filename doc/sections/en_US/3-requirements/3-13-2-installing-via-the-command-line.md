### Installing via the command line

The Wt used to be packaged as the `witty` and `witty-dev` packages, but no Ubuntu 24.04/26.04 or Debian 13 release has them any more, so the project configure builds the fetched Wt sources there.

The `install-ubuntu-24-04.sh`, `install-ubuntu-26-04.sh` and `install-debian-13.sh` scripts of the [scripts/packages](/scripts/packages) directory build that Wt `4.11.4` release out of its sources and install it system wide, the way the [Cloning and building from sources](/doc/sections/en_US/3-requirements/3-13-1-cloning-and-building-from-sources.md) subsection does by hand, so the project configure finds the installed Wt afterwards instead of fetching it.

FreeBSD packages the Wt as the `wt` port:

```
sudo pkg install -y wt
```
