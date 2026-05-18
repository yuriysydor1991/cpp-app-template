## Optional for the libcurl integration

In order to enable the libcurl integration in the template project install the system development package for the [libcurl](https://curl.se/) library (GNU/Linux based):

```
sudo apt install -y libcurl4-openssl-dev
```

Alternative SSL backends ship as `libcurl4-gnutls-dev` or `libcurl4-nss-dev` - pick the one that matches the rest of your system stack.

For more details on how to enable the libcurl target examine the [Enabling the libcurl](/doc/sections/en_US/5-14-enabling-libcurl.md) section.
