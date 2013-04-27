frequencies = [ 2440, 2389, 2413, 2599, 2761, 2823, 3030, 3139, 3326, 3419, 3457, 3507, 3333, 3248, 2971, 2837, 2639, 2583, 2431, 2382; 4344, 4623, 5017, 5706, 6516, 7361, 8905, 9986, 10951, 11565, 11595, 11544, 10693, 9627, 8488, 7132, 6177, 5442, 4887, 4527; 2943, 3234, 3778, 4737, 6404, 8793, 11502, 15189, 18435, 20585, 21288, 20263, 17639, 14167, 11022, 8171, 5879, 4526, 3560, 3112; 754, 824, 1211, 1713, 2998, 5529, 9770, 16247, 23446, 28816, 30775, 27990, 21364, 14424, 8627, 4690, 2562, 1582, 1090, 812; 25, 32, 64, 154, 398, 1267, 3717, 10112, 21701, 33929, 38731, 31420, 18269, 8129, 2852, 902, 287, 105, 45, 29; 0, 0, 0, 0, 3, 25, 246, 1949, 10695, 31393, 42566, 25623, 7117, 1230, 147, 16, 1, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 7, 814, 14530, 39421, 7818, 318, 5, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 334, 18294, 34, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 4, 218, 1665, 66, 1, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 9, 8, 1, 0, 0, 0, 0, 0, 0, 0 ];
expFrequencies = [ 9104.18, 9190.02, 9407.95, 9742.62, 10168, 10646.8, 11132.7, 11574.7, 11924.1, 12141.8, 12203.3, 12101.7, 11848.5, 11472, 11014.4, 10525.6, 10056, 9650.05, 9342.3, 9156.07; 17650.8, 18119.5, 19341.1, 21304, 23945.7, 27103.9, 30485.5, 33686.6, 36277.1, 37906.4, 38367.7, 37606.2, 35713.4, 32934.2, 29647.5, 26286.9, 23234.6, 20750.6, 18968.4, 17933.3; 12072.8, 12765.1, 14666.4, 18017.1, 23101.7, 30033.8, 38434.7, 47215.2, 54784.5, 59683, 61080.1, 58775.5, 53110, 45087.5, 36263.4, 28153.2, 21668.4, 17035.6, 14071.4, 12487.5; 2957.52, 3294.07, 4312.07, 6444.41, 10521.2, 17758, 29190.3, 44253.2, 59618.1, 70526.4, 73738.9, 68460.2, 56047.5, 40317.9, 25953.9, 15600.3, 9267.98, 5774.69, 3978.64, 3156.96; 111.772, 137.366, 230.078, 498.083, 1288.99, 3624.55, 9953.3, 23882.5, 45463.2, 65465, 72035.6, 61392.6, 39753.2, 19583, 7813.86, 2799.62, 1006.61, 403.18, 197.191, 126.634; 0.0372205, 0.0585573, 0.180884, 0.965239, 7.42139, 66.7262, 569.276, 3829.06, 17175.8, 43012.8, 55159.2, 36451.2, 12419.1, 2463.27, 339.92, 38.608, 4.37574, 0.611386, 0.129204, 0.048979; 3.77726e-014, 1.61057e-013, 5.44287e-012, 8.76537e-010, 3.70036e-007, 0.000216674, 0.0937932, 17.2504, 914.769, 12146.6, 27764.6, 7306.14, 388.618, 5.26178, 0.0221383, 4.4874e-005, 7.82743e-008, 2.2206e-010, 1.92459e-012, 9.1218e-014; 0, 0, 0, 0, 0, 0, 0, 6.78323e-017, 6.8027e-005, 141.468, 3156.08, 12.5537, 2.38333e-007, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
colormap(jet);
clf; subplot(2,1,1);
imagesc(frequencies);
title('Observed frequencies');
axis equal;
subplot(2,1,2);
imagesc(expFrequencies);
axis equal;
title('Expected frequencies');
