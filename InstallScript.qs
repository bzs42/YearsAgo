function Component()
{
    // constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        component.addOperation(
            "CreateShortcut",
            "@TargetDir@/bin/YearsAgo.exe",
            "@StartMenuDir@/YearsAgo.lnk",
            "workingDirectory=@TargetDir@",
            "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2",
            "description=Start Years Ago Appplication");
    }
}
