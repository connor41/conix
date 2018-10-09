#include "../headers/conix.h"
#include "../headers/multiboot.h"

void main(int bootloader_inf, multiboot_info_t* loader_struct_addr){
  textGraphickInit();

  if(bootloader_inf == MULTIBOOT_BOOTLOADER_MAGIC) printf("%s", "Loaded via GRUB\n");

  printf("%s", "Conix Core version: 0.02\n");
  printf("%s", "Load kernel...\n");
	printf("%s", "/----------------------------------------\\\n");
  setScreenTextColor(RED);
  printf("%s", "|    AVE SATAN, AVE CONNOR41, AVE GNU!   |\n");
  setScreenTextColor(LIGHT_GREY);
	printf("%s", "\\----------------------------------------/\n");
  updateScreen();

  initKernelShell();

  return;
}
