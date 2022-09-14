setws VitisWorkspace;
platform create -name HCCPlatform -hw Export/top_wrapper.xsa -proc ps7_cortexa9 -os linux -fsbl-target psu_cortexa53_0;
domain config -sysroot HCCLinux/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi;
platform write;
platform generate;

app create -name simplegpio-example -platform HCCPlatform -os linux -lang c++ -template "Empty Application (C++)";
app build simplegpio-example;

app create -name stream-example -platform HCCPlatform -os linux -lang c++ -template "Empty Application (C++)";
app build stream-example;

