savedcmd_drv_coredumpers.mod := printf '%s\n'   drv_coredumpers.o | awk '!x[$$0]++ { print("./"$$0) }' > drv_coredumpers.mod
