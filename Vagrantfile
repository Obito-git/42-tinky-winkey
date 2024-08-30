Vagrant.configure("2") do |config|
  config.vm.box = "gusztavvargadr/windows-11"
  config.vm.box_version = "2302.0.2407"

  config.vm.provider "virtualbox" do |v|
    v.gui = true
    v.memory = 10000
    v.cpus = 12
    v.customize ["modifyvm", :id, "--vram", "256", "--monitorcount", "1"]
    v.customize ["storageattach", :id,
                 "--storagectl", "IDE Controller",
                 "--port", "0", "--device", "1",
                 "--type", "dvddrive",
                 "--medium", "emptydrive"]
  end

  config.vm.provision "shell", privileged: "true", powershell_elevated_interactive: "true", inline: <<-SHELL
    # Install chocolatey (Windows package manager)
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

    # Install Visual Studio 2022 Build Tools for C compilation
    choco install visualstudio2022buildtools --version=17.4.5.1 -y
    choco install visualstudio2022-workload-vctools -y
    choco install drmemory -y

    # Make cl command available in the shell
    $msvcPath = Get-ChildItem -Directory 'C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC' | Sort-Object Name | Select-Object -Last 1
    $clPath = Join-Path $msvcPath.FullName 'bin\\Hostx64\\x64'
    $env:Path += ';' + $clPath
    [Environment]::SetEnvironmentVariable('Path', $env:Path, [EnvironmentVariableTarget]::Machine)

    # TODO: rename batch name
    $script = '@echo on
    set currPath=%cd%
    call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Auxiliary\\Build\\vcvars64.bat"
    cd %currPath%
    set PreferredToolArchitecture=x64
    cl %*' | Out-File 'C:\\build_vs.bat' -Encoding Ascii
  
  SHELL
end
