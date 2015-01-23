#
# Makefile for the Linux network device drivers.
#

#
# Networking Core Drivers
#
obj-$(CONFIG_BONDING) += bonding/

obj-$(CONFIG_SUNDANCE) += sundance.o
obj-$(CONFIG_HAMACHI) += hamachi.o
obj-$(CONFIG_NET) += Space.o loopback.o
obj-$(CONFIG_SEEQ8005) += seeq8005.o
obj-$(CONFIG_NET_SB1000) += sb1000.o
obj-$(CONFIG_MAC8390) += mac8390.o
obj-$(CONFIG_APNE) += apne.o 8390.o
obj-$(CONFIG_PCMCIA_PCNET) += 8390.o
obj-$(CONFIG_HP100) += hp100.o
obj-$(CONFIG_SMC9194) += smc9194.o
obj-$(CONFIG_FEC) += fec.o
obj-$(CONFIG_FEC_MPC52xx) += fec_mpc52xx.o
ifeq ($(CONFIG_FEC_MPC52xx_MDIO),y)
	obj-$(CONFIG_FEC_MPC52xx) += fec_mpc52xx_phy.o
endif
obj-$(CONFIG_68360_ENET) += 68360enet.o
obj-$(CONFIG_WD80x3) += wd.o 8390.o
obj-$(CONFIG_EL2) += 3c503.o 8390p.o
obj-$(CONFIG_NE2000) += ne.o 8390p.o
obj-$(CONFIG_NE2_MCA) += ne2.o 8390p.o
obj-$(CONFIG_HPLAN) += hp.o 8390p.o
obj-$(CONFIG_HPLAN_PLUS) += hp-plus.o 8390p.o
obj-$(CONFIG_ULTRA) += smc-ultra.o 8390.o
obj-$(CONFIG_ULTRAMCA) += smc-mca.o 8390.o
obj-$(CONFIG_ULTRA32) += smc-ultra32.o 8390.o
obj-$(CONFIG_E2100) += e2100.o 8390.o
obj-$(CONFIG_ES3210) += es3210.o 8390.o
obj-$(CONFIG_LNE390) += lne390.o 8390.o
obj-$(CONFIG_NE3210) += ne3210.o 8390.o
obj-$(CONFIG_SB1250_MAC) += sb1250-mac.o
obj-$(CONFIG_B44) += b44.o
obj-$(CONFIG_FORCEDETH) += forcedeth.o
obj-$(CONFIG_NE_H8300) += ne-h8300.o
obj-$(CONFIG_AX88796) += ax88796.o
obj-$(CONFIG_BCM63XX_ENET) += bcm63xx_enet.o
obj-$(CONFIG_FTMAC100) += ftmac100.o

obj-$(CONFIG_TSI108_ETH) += tsi108_eth.o
obj-$(CONFIG_MV643XX_ETH) += mv643xx_eth.o
ll_temac-objs := ll_temac_main.o ll_temac_mdio.o
obj-$(CONFIG_XILINX_LL_TEMAC) += ll_temac.o
obj-$(CONFIG_XILINX_EMACLITE) += xilinx_emaclite.o
obj-$(CONFIG_QLA3XXX) += qla3xxx.o
obj-$(CONFIG_QLCNIC) += qlcnic/
obj-$(CONFIG_QLGE) += qlge/

obj-$(CONFIG_PPP) += ppp_generic.o
obj-$(CONFIG_PPP_ASYNC) += ppp_async.o
obj-$(CONFIG_PPP_SYNC_TTY) += ppp_synctty.o
obj-$(CONFIG_PPP_DEFLATE) += ppp_deflate.o
obj-$(CONFIG_PPP_BSDCOMP) += bsd_comp.o
obj-$(CONFIG_PPP_MPPE) += ppp_mppe.o
obj-$(CONFIG_PPPOE) += pppox.o pppoe.o
obj-$(CONFIG_PPPOL2TP) += pppox.o
obj-$(CONFIG_PPTP) += pppox.o pptp.o
obj-$(CONFIG_PPPOLAC) += pppox.o pppolac.o
obj-$(CONFIG_PPPOPNS) += pppox.o pppopns.o

obj-$(CONFIG_SLIP) += slip.o
obj-$(CONFIG_SLHC) += slhc.o

obj-$(CONFIG_XEN_NETDEV_FRONTEND) += xen-netfront.o
obj-$(CONFIG_XEN_NETDEV_BACKEND) += xen-netback/

obj-$(CONFIG_DUMMY) += dummy.o
obj-$(CONFIG_EQUALIZER) += eql.o
obj-$(CONFIG_IFB) += ifb.o
obj-$(CONFIG_MACVLAN) += macvlan.o
obj-$(CONFIG_MACVTAP) += macvtap.o
obj-$(CONFIG_MII) += mii.o
obj-$(CONFIG_MDIO) += mdio.o
obj-$(CONFIG_NET) += Space.o loopback.o
obj-$(CONFIG_NETCONSOLE) += netconsole.o
obj-$(CONFIG_PHYLIB) += phy/
obj-$(CONFIG_RIONET) += rionet.o
obj-$(CONFIG_NET_TEAM) += team/
obj-$(CONFIG_TUN) += tun.o
obj-$(CONFIG_VETH) += veth.o
obj-$(CONFIG_VIRTIO_NET) += virtio_net.o

#
# Networking Drivers
#
obj-$(CONFIG_ARCNET) += arcnet/
obj-$(CONFIG_DEV_APPLETALK) += appletalk/
obj-$(CONFIG_CAIF) += caif/
obj-$(CONFIG_CAN) += can/
obj-$(CONFIG_ETRAX_ETHERNET) += cris/
obj-$(CONFIG_NET_DSA) += dsa/
obj-$(CONFIG_ETHERNET) += ethernet/
obj-$(CONFIG_FDDI) += fddi/
obj-$(CONFIG_HIPPI) += hippi/
obj-$(CONFIG_HAMRADIO) += hamradio/
obj-$(CONFIG_IRDA) += irda/
obj-$(CONFIG_PLIP) += plip/
obj-$(CONFIG_PPP) += ppp/
obj-$(CONFIG_PPP_ASYNC) += ppp/
obj-$(CONFIG_PPP_BSDCOMP) += ppp/
obj-$(CONFIG_PPP_DEFLATE) += ppp/
obj-$(CONFIG_PPP_MPPE) += ppp/
obj-$(CONFIG_PPP_SYNC_TTY) += ppp/
obj-$(CONFIG_PPPOE) += ppp/
obj-$(CONFIG_PPPOL2TP) += ppp/
obj-$(CONFIG_PPTP) += ppp/
obj-$(CONFIG_SLIP) += slip/
obj-$(CONFIG_SLHC) += slip/
obj-$(CONFIG_NET_SB1000) += sb1000.o
obj-$(CONFIG_SUNGEM_PHY) += sungem_phy.o
obj-$(CONFIG_TR) += tokenring/
obj-$(CONFIG_WAN) += wan/
obj-$(CONFIG_WLAN) += wireless/
obj-$(CONFIG_WIMAX) += wimax/

obj-$(CONFIG_VMXNET3) += vmxnet3/
obj-$(CONFIG_XEN_NETDEV_FRONTEND) += xen-netfront.o
obj-$(CONFIG_XEN_NETDEV_BACKEND) += xen-netback/

obj-$(CONFIG_USB_CATC)          += usb/
obj-$(CONFIG_USB_KAWETH)        += usb/
obj-$(CONFIG_USB_PEGASUS)       += usb/
obj-$(CONFIG_USB_RTL8150)       += usb/
obj-$(CONFIG_USB_HSO)		+= usb/
obj-$(CONFIG_USB_USBNET)        += usb/
obj-$(CONFIG_USB_ZD1201)        += usb/
obj-$(CONFIG_USB_IPHETH)        += usb/
obj-$(CONFIG_USB_CDC_PHONET)   += usb/

obj-$(CONFIG_WLAN) += wireless/
obj-$(CONFIG_NET_TULIP) += tulip/
obj-$(CONFIG_HAMRADIO) += hamradio/
obj-$(CONFIG_IRDA) += irda/
obj-$(CONFIG_ETRAX_ETHERNET) += cris/
obj-$(CONFIG_ENP2611_MSF_NET) += ixp2000/

obj-$(CONFIG_NETCONSOLE) += netconsole.o

obj-$(CONFIG_FS_ENET) += fs_enet/

obj-$(CONFIG_NETXEN_NIC) += netxen/
obj-$(CONFIG_NIU) += niu.o
obj-$(CONFIG_VIRTIO_NET) += virtio_net.o
obj-$(CONFIG_SFC) += sfc/

obj-$(CONFIG_WIMAX) += wimax/
obj-$(CONFIG_CAIF) += caif/

obj-$(CONFIG_OCTEON_MGMT_ETHERNET) += octeon/
obj-$(CONFIG_PCH_GBE) += pch_gbe/
obj-$(CONFIG_TILE_NET) += tile/

ifdef CONFIG_PHONET
obj-$(CONFIG_U8500_SHRM) += u8500_shrm.o
obj-$(CONFIG_MODEM_M6718_SPI) += m6718_modem_net.o
endif
