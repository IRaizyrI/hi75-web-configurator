// Expected layout comes from the saved application image, not a live WebHID
// descriptor. A match is deliberately never promoted to exact identification.
const EXPECTED = Object.freeze({ vendorId: 0x258a, productId: 0x010c });

function asArray(value) {
  return Array.from(value ?? []);
}

function reportBits(report) {
  return asArray(report.items).reduce((total, item) => {
    const size = item.reportSize;
    const count = item.reportCount;
    return Number.isSafeInteger(size) && Number.isSafeInteger(count)
      ? total + size * count
      : NaN;
  }, 0);
}

function reports(collection, kind) {
  return asArray(collection[kind]);
}

function allCollections(collections) {
  return asArray(collections).flatMap((collection) => [
    collection,
    ...allCollections(collection.children),
  ]);
}

function hasReport(collection, kind, id, bits) {
  return reports(collection, kind).some(
    (report) => report.reportId === id && reportBits(report) === bits,
  );
}

export function assessCandidate(device) {
  const checks = {
    vidPid: device.vendorId === EXPECTED.vendorId && device.productId === EXPECTED.productId,
    vendorCollection: false,
    inputId2: false,
    inputId3: false,
    featureId5: false,
    featureId6: false,
    inputId6: false,
    pairedId6: false,
  };
  const all = allCollections(device.collections);
  const vendorCollections = all.filter(
    (collection) => collection.usagePage === 0xff00 && collection.usage === 1,
  );
  checks.vendorCollection = vendorCollections.length > 0;
  checks.inputId2 = all.some((c) => c.usagePage === 0x000c && c.usage === 1 && hasReport(c, "inputReports", 2, 16));
  checks.inputId3 = vendorCollections.some((c) => hasReport(c, "inputReports", 3, 24));
  checks.featureId5 = vendorCollections.some((c) => hasReport(c, "featureReports", 5, 40));
  checks.featureId6 = vendorCollections.some((c) => hasReport(c, "featureReports", 6, 4152));
  checks.inputId6 = vendorCollections.some((c) => hasReport(c, "inputReports", 6, 56));
  checks.pairedId6 = vendorCollections.some((c) =>
    hasReport(c, "inputReports", 6, 56) && hasReport(c, "featureReports", 6, 4152));
  const layoutMatch = Object.values(checks).every(Boolean);
  return {
    status: layoutMatch ? "descriptor-layout candidate" : checks.vidPid ? "unconfirmed 258A:010C device" : "different VID:PID",
    checks,
    exactModelVerified: false,
    revisionVerified: false,
    configurationReadAllowed: false,
    writesAllowed: false,
  };
}

function itemSnapshot(item) {
  const keys = [
    "usagePage", "usages", "usageMinimum", "usageMaximum", "reportSize",
    "reportCount", "unitExponent", "unitSystem", "unitFactorLengthExponent",
    "unitFactorMassExponent", "unitFactorTimeExponent", "unitFactorTemperatureExponent",
    "unitFactorCurrentExponent", "unitFactorLuminousIntensityExponent", "logicalMinimum",
    "logicalMaximum", "physicalMinimum", "physicalMaximum", "isAbsolute",
    "isArray", "isBufferedBytes", "isConstant", "isLinear", "isRange",
    "isRelative", "isVolatile", "hasNull", "hasPreferredState", "wrap",
  ];
  const result = {};
  for (const key of keys) {
    if (item[key] !== undefined) result[key] = item[key];
  }
  return result;
}

function reportSnapshot(report) {
  const items = asArray(report.items).map(itemSnapshot);
  const bits = reportBits(report);
  return {
    reportId: report.reportId,
    payloadBits: Number.isFinite(bits) ? bits : null,
    payloadBytes: Number.isFinite(bits) ? Math.ceil(bits / 8) : null,
    items,
  };
}

function collectionSnapshot(collection) {
  return {
    usagePage: collection.usagePage,
    usage: collection.usage,
    collectionType: collection.type ?? null,
    inputReports: reports(collection, "inputReports").map(reportSnapshot),
    outputReports: reports(collection, "outputReports").map(reportSnapshot),
    featureReports: reports(collection, "featureReports").map(reportSnapshot),
    children: asArray(collection.children).map(collectionSnapshot),
  };
}

export function deviceSnapshot(device) {
  return {
    vendorId: device.vendorId,
    productId: device.productId,
    productName: device.productName ?? null,
    collections: asArray(device.collections).map(collectionSnapshot),
    assessment: assessCandidate(device),
  };
}
