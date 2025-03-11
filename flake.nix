{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "vagrant-environment";

  buildInputs = [
    pkgs.vagrant
  ];

  # Optional: Additional environment setup
  shellHook = ''
    echo "Vagrant installion successfull"
    vagrant plugin install vagrant-cachier
  '';
}
