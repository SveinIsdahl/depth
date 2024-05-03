import torch

# Zoe_N
model_zoe_n = torch.hub.load("ZoeDepth", "ZoeD_N", source="local", pretrained=True)

##### sample prediction
DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
DEVICE = "cpu"
zoe = model_zoe_n.to(DEVICE)


# Local file
from PIL import Image
image = Image.open("test.jpg").convert("RGB")  # load
depth = zoe.infer_pil(image)  # as numpy

#depth = zoe.infer_pil(image, output_type="pil")  # as 16-bit PIL Image

#depth = zoe.infer_pil(image, output_type="tensor")  # as torch tensor

# Tensor 
from zoedepth.utils.misc import pil_to_batched_tensor
from zoedepth.utils.misc import colorize
#X = pil_to_batched_tensor(image).to(DEVICE)
#depth_tensor = zoe.infer(X)

colored = colorize(depth)
fpath_colored = "out.png"
Image.fromarray(colored).save(fpath_colored)

