frequencies = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 7, 4, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 247, 9141, 18241, 2297, 19, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 707, 160210, 434263, 19374, 15, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 75269, 272412, 3635, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 580, 3555, 2, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
expFrequencies = [ 1.07753e-006, 8.43233e-007, 8.04111e-007, 9.26572e-007, 1.32426e-006, 2.54313e-006, 8.06075e-006, 6.85542e-005, 0.00217084, 0.0954413, 1.98007, 11.8103, 17.051, 5.81597, 0.508833, 0.0154437, 0.000347607, 2.02275e-005, 4.1952e-006, 1.76199e-006; 1.09556e-014, 7.64056e-016, 4.32465e-016, 2.23289e-015, 7.82117e-014, 1.18881e-011, 4.71645e-009, 2.98891e-006, 0.00219699, 1.87973, 768.278, 27213.8, 54846.5, 6746.72, 49.476, 0.066634, 8.3926e-005, 1.20558e-007, 2.26589e-010, 8.58912e-013; 0, 0, 0, 0, 0, 0, 3.48954e-018, 6.80456e-012, 3.35217e-006, 0.280424, 1995.89, 423901, 1.14442e+006, 52364, 35.5932, 0.00138421, 6.18428e-009, 7.57687e-015, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 2.77698e-014, 2.28012e-005, 62.0984, 173325, 627032, 8711.77, 0.0931094, 1.71507e-009, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.47296e-016, 0.00102265, 1103.06, 6572.52, 7.36134, 5.58188e-009, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.32484e-015, 0.0161759, 0.280298, 4.50382e-007, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.3651e-012, 3.64311e-009, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
colormap(jet);
clf; subplot(2,1,1);
imagesc(frequencies);
title('Observed frequencies');
axis equal;
subplot(2,1,2);
imagesc(expFrequencies);
axis equal;
title('Expected frequencies');
