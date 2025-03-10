## VARIABLES
VM_IP = "192.168.56.110"
VM_NAME = "ft-ping"

MEM = 4096
CORE = 4
 
Vagrant.configure("2") do |config|
    config.vm.box = "debian/bookworm64"
  
    config.vm.define VM_NAME do |controller|
    controller.vm.hostname = VM_NAME
    controller.vm.provider "virtualbox" do |v|
        v.memory = MEM
        v.cpus = CORE
        v.name = VM_NAME
    end
    controller.vm.network "private_network", type: "static", ip: VM_IP
    controller.vm.synced_folder ".", "/vagrant", type: "virtualbox"
    controller.vm.provision "shell", inline: <<-SHELL
        apt-get update -y
        apt-get install make gcc clang valgrind -y
        cd /vagrant/ && make get_ping
    SHELL
end
end