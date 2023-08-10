echo "----------------FILENAME---------------------"
leaks -atExit -- ./cub3D maps/errors_filename/dossier.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_filename/.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_filename/name.cu

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_filename/name..cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_filename/name.cubbbb

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_filename/name.txt




echo "--------------INITIALIZATION------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid_ceil.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid00.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid10.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid11.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid12.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid14.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid16.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid17.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid18.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid19.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid20.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid22.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid25.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_init/Invalid25.cub



echo "--------------------MAPS----------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid1.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid2.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid3.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid4.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid5.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid6.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid7.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid8.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid9.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid10.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid13.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid21.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid23.cub

echo "---------------------------------------------"
leaks -atExit -- ./cub3D maps/errors_map/Invalid24.cub

