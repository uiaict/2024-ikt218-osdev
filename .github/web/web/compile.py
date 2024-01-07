import pathlib
import logging
import jinja2
import shutil

_LOGGER = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

def main():
    current_dir = pathlib.Path(__file__).parent
    static_dir = current_dir.joinpath("static")
    template_dir = current_dir.joinpath("templates")
    os_dir = static_dir.joinpath("os")
    index_file = static_dir.joinpath("index.html")

    # Create necessary directories
    static_dir.mkdir(exist_ok=True)
    os_dir.mkdir(exist_ok=True)

    os_list = []
    for build_dir in current_dir.parent.parent.parent.joinpath("build").glob("*"):
        group_name = build_dir.name
        images = list(build_dir.glob("*.iso"))

        os_dict = {"disk": "", "kernel": ""}

        for image in images:
            print(image.name)
            if image.name.endswith("disk.iso"):
                os_dict["disk"] = image
            elif image.name.endswith("kernel.iso"):
                os_dict["kernel"] = image

        if os_dict["disk"] and os_dict["kernel"]:
            disk_group_named = f"{group_name}-{os_dict['disk'].name}"
            kernel_group_named = f"{group_name}-{os_dict['kernel'].name}"
            
            shutil.copy(os_dict["disk"], os_dir.joinpath(disk_group_named))
            shutil.copy(os_dict["kernel"], os_dir.joinpath(kernel_group_named))
            os_dict["disk"] = disk_group_named
            os_dict["kernel"] = kernel_group_named
            os_dict["name"] = group_name
            os_list.append(os_dict)
            
    templateLoader = jinja2.FileSystemLoader(searchpath=template_dir)
    templateEnv = jinja2.Environment(loader=templateLoader)
    template = templateEnv.get_template("index.html")
    outputText = template.render(os_list=os_list)

    with index_file.open("w+") as f:
        f.write(outputText)

if __name__ == "__main__":
    main()
