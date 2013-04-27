frequencies = [ 3616, 3547, 3500, 3477, 3405, 3299, 3159, 3105, 2972, 2954, 2999, 2965, 2934, 3063, 3021, 3119, 3298, 3295, 3379, 3407; 11041, 10881, 10741, 10570, 9940, 9265, 8621, 8318, 7658, 7175, 7183, 7024, 7160, 7281, 7782, 8253, 8912, 9510, 10156, 10476; 17368, 17680, 17449, 16304, 14794, 13206, 11595, 10007, 8754, 8068, 7650, 7303, 7666, 8179, 9112, 10382, 11814, 13576, 15366, 16574; 21820, 22203, 21462, 18994, 15970, 12723, 9899, 7593, 6216, 5191, 4609, 4487, 4823, 5389, 6446, 8242, 10487, 13530, 16720, 19660; 20956, 22417, 20487, 16842, 11994, 7898, 4983, 3137, 2039, 1534, 1217, 1161, 1283, 1619, 2181, 3379, 5412, 8486, 12923, 17684; 15171, 17047, 14171, 9241, 4632, 2047, 814, 309, 158, 80, 69, 33, 87, 98, 183, 444, 1018, 2457, 5429, 10055; 5979, 7719, 5203, 1877, 391, 88, 11, 0, 0, 0, 1, 0, 0, 0, 0, 3, 23, 97, 643, 2462; 676, 1332, 431, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 51; 3, 30, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
expFrequencies = [ 13352.4, 13383.2, 13334.9, 13212.4, 13027.9, 12800.1, 12551.9, 12308, 12092.3, 11925.2, 11822.2, 11792.5, 11839, 11957.3, 12136.7, 12360.6, 12607.6, 12853.3, 13073.4, 13245.5; 39034.2, 39258.8, 38907.1, 38015.7, 36679.8, 35044.5, 33287.3, 31591.3, 30120.1, 29001.2, 28321, 28126.8, 28431.4, 29214.5, 30420.6, 31954.3, 33679.1, 35425.3, 37008.5, 38256.6; 57649.2, 58302.8, 57280, 54707.6, 50916.1, 46404.2, 41742.1, 37447.4, 33897.6, 31312, 29789.5, 29361.8, 30034, 31797.2, 34609.1, 38348.8, 42763.6, 47440.7, 51841.1, 55399.8; 63107.2, 64479.3, 62337, 57072.3, 49669.3, 41467.6, 33734.2, 27302.7, 22496.9, 19289.1, 17515.8, 17033, 17794.7, 19872.2, 23422.9, 28596.8, 35362.4, 43290.7, 51434.1, 58470.8; 52517.1, 54822.8, 51243.7, 42951.1, 32539.1, 22735.3, 15148.1, 10038.7, 6916.18, 5157.01, 4294.82, 4073.61, 4425.26, 5457.61, 7472.23, 10980.5, 16613.4, 24757.2, 34886.9, 45082.9; 29925.1, 32858.6, 28371.3, 19385.9, 10763.5, 5129.26, 2262.84, 1004.2, 485.962, 275.531, 193.702, 174.968, 205.181, 307.355, 564.639, 1197.37, 2721.12, 6106.39, 12460.6, 21510.8; 8686.81, 10935.6, 7629.36, 3101.67, 824.691, 163.981, 28.0503, 4.83195, 0.991686, 0.284714, 0.130553, 0.104168, 0.148329, 0.362341, 1.37735, 7.07935, 41.7585, 239.166, 1140.76, 3949.17; 601.07, 1158.21, 418.886, 36.9056, 1.01648, 0.0111085, 6.91869e-005, 3.90822e-007, 3.34317e-009, 7.20642e-011, 6.20509e-012, 3.01774e-012, 9.30487e-012, 1.52354e-010, 9.05557e-009, 1.21424e-006, 0.00021969, 0.0323125, 2.47266, 70.5124; 0.628313, 7.91817, 0.112692, 1.67293e-007, 2.57361e-017, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8.1857e-015, 7.50127e-006; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
colormap(jet);
clf; subplot(2,1,1);
imagesc(frequencies);
title('Observed frequencies');
axis equal;
subplot(2,1,2);
imagesc(expFrequencies);
axis equal;
title('Expected frequencies');
