do_image_wic[postfuncs] += "nxp_imx9_wic"

nxp_imx9_wic() {
    if [ "${CUSTOMER_BUILD_BOOTLOADER}" = "1" ]; then
        for config in ${UBOOT_CONFIG}; do
            cd "${DEPLOY_DIR_IMAGE}"

            ofname=${IMAGE_BASENAME}${IMAGE_MACHINE_SUFFIX}-${config}${IMAGE_NAME_SUFFIX}${IMAGE_VERSION_SUFFIX}.wic
            cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.wic ${IMGDEPLOYDIR}/$ofname
            dd if=imx-boot-nxp-imx9-${UBOOT_CONFIG}.bin-flash_singleboot of=${IMGDEPLOYDIR}/$ofname bs=512 seek=64 conv=fsync,notrunc

            cd "${IMGDEPLOYDIR}"
            bmaptool create "$ofname" -o "${ofname}.bmap"
            linkname="${IMAGE_LINK_NAME}-${config}.wic"
            ln -sf $ofname $linkname
        done
        # Remove the default wic file
        rm -rf "${IMGDEPLOYDIR}/${IMAGE_LINK_NAME}.wic"
        rm -rf "${IMGDEPLOYDIR}/${IMAGE_LINK_NAME}.wic.bmap"
        rm -rf "${IMGDEPLOYDIR}/${IMAGE_NAME}.wic"
        rm -rf "${IMGDEPLOYDIR}/${IMAGE_NAME}.wic.bmap"
    fi

}
