{
  description = "PKArch Developement Flake";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-26.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        
        # Access the RISC-V 32-bit cross-compilation toolchain
        i686Pkgs = pkgs.pkgsCross.i686-elf;
        x64Pkgs = pkgs.pkgsCross.x86_64-elf;
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.verilator
            pkgs.gtkwave
            pkgs.zlib

            i686Pkgs.buildPackages.gcc
            i686Pkgs.buildPackages.binutils

            x64Pkgs.buildPackages.gcc
            x64Pkgs.buildPackages.binutils
          ];
        };
      });
}

